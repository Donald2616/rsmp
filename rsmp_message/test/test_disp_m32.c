#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disp_m32.h"
#include "disp_json_generic.h"

int main() {
    printf("========== ENCODAGE M32 ==========\n");

    // Création d'une commande de suppression DISP/M32
    DispM32CommandRequest req;
    req.msgIdCount = 2;
    req.msgIdList = calloc(req.msgIdCount, sizeof(char*));
    req.msgIdList[0] = strdup("MSG_BIENVENUE");
    req.msgIdList[1] = strdup("ACCIDENT_VOIE_GAUCHE");

    // Encodage en JSON via la fonction générique
    struct json_object* json = encode_disp_m32_command_request(&req);
    if (json) {
        printf("JSON généré (CommandRequest) :\n%s\n\n",
               json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY));
        json_object_put(json);
    }

    // Libération de la requête
    free_disp_m32_command_request(&req);

    printf("========== DECODAGE M32 ==========\n");

    // Réponse JSON simulée
    const char* response_json = "{ \
        \"retMessages\": [ \
            { \
                \"msgId\": \"MSG_BIENVENUE\", \
                \"retStatus\": { \
                    \"code\": \"RS_UNKNOWN_ID\", \
                    \"rea\": \"Unknown message ID \\\"MSG_BIENVENUE\\\"\" \
                } \
            }, \
            { \
                \"msgId\": \"ACCIDENT_VOIE_GAUCHE\", \
                \"retStatus\": { \
                    \"code\": \"RS_OK\", \
                    \"rea\": \"\\\"ACCIDENT_VOIE_GAUCHE\\\" deleted\" \
                } \
            } \
        ] \
    }";

    DispM32CommandResponse res;
    if (decode_disp_m32_command_response(response_json, &res) == 0) {
        printf("Structure décodée (CommandResponse) :\n");
        for (int i = 0; i < res.retMessageCount; ++i) {
            printf("  msgId: %s\n", res.retMessages[i].msgId);
            printf("    -> code: %s\n", res.retMessages[i].retStatus.code);
            printf("    -> reason: %s\n", res.retMessages[i].retStatus.rea);
        }

        free_disp_m32_command_response(&res);
    } else {
        printf("Erreur de décodage JSON.\n");
    }

    return 0;
}

void free_disp_m32_command_response(DispM32CommandResponse* res) {
    if (!res || !res->retMessages) return;
    free(res->retMessages);
    res->retMessages = NULL;
    res->retMessageCount = 0;
}
