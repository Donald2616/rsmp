#include <stdio.h>
#include <stdlib.h>
#include "disp_m31.h"
#include "disp_json_generic.h"


int main() {
    printf("========== ENCODAGE ==========\n");

    // === Construction manuelle d'une commande DISP/M31 (comme un superviseur)
    DispM31CommandRequest req;
    req.messageCount = 1;
    req.messages = calloc(1, sizeof(MessageObject));

    MessageObject* msg = &req.messages[0];
    snprintf(msg->msgId, sizeof(msg->msgId), "HELLO_WORLD");
    msg->repeatCount = 0;

    msg->sequenceCount = 1;
    msg->sequences = calloc(1, sizeof(Sequence));
    Sequence* seq = &msg->sequences[0];
    snprintf(seq->templateId, sizeof(seq->templateId), "TPL1");
    snprintf(seq->end, sizeof(seq->end), "Infinite");

    seq->animationCount = 1;
    seq->animations = calloc(1, sizeof(Animation));
    Animation* anim = &seq->animations[0];
    snprintf(anim->zoneId, sizeof(anim->zoneId), "ZONE1");
    snprintf(anim->animType, sizeof(anim->animType), "FIX");

    anim->contentCount = 1;
    anim->contents = calloc(1, sizeof(Content));
    Content* content = &anim->contents[0];
    snprintf(content->contentType, sizeof(content->contentType), "Text");
    snprintf(content->contextText, sizeof(content->contextText), "Hello World");
    content->duration.onDuration = 100;

    // === Encodage vers JSON
    struct json_object* json = encode_disp_m31_command_request(&req);
    printf("JSON généré (CommandRequest) :\n%s\n\n", json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY));

    // Nettoyage
    json_object_put(json);
    free_disp_m31_command_request(&req);

    printf("========== DECODAGE ==========\n");

    // === Simulation d'une réponse JSON du contrôleur (CommandResponse)
    const char* response_json = "{                                       \
        \"retMessages\": [                                                \
            {                                                             \
                \"msgId\": \"HELLO_WORLD\",                               \
                \"retStatus\": {                                          \
                    \"code\": \"RS_OK\",                                  \
                    \"rea\": \"HELLO_WORLD ajouté avec succès !\"        \
                }                                                         \
            }                                                             \
        ]                                                                 \
    }";

    // === Décodage vers structure C
    DispM31CommandResponse response;
    if (decode_disp_m31_command_response(response_json, &response) == 0) {
        printf("Structure décodée (CommandResponse) :\n");
        for (int i = 0; i < response.retMessageCount; ++i) {
            printf("  msgId: %s\n", response.retMessages[i].msgId);
            printf("  -> code: %s\n", response.retMessages[i].retStatus.code);
            printf("  -> reason: %s\n", response.retMessages[i].retStatus.rea);
        }

        // Libération mémoire
        free(response.retMessages);
    } else {
        printf("Erreur de décodage de la réponse JSON.\n");
    }

    return 0;
}
