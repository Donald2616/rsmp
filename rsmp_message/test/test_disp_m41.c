#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include "disp_m41.h"
#include "disp_json_generic.h"

int main() {
    // ==== ENCODAGE M41 ====
    printf("=========== ENCODAGE M41 ===========\n");

    DispM41CommandRequest req;
    memset(&req, 0, sizeof(req));

    strncpy(req.msgId, "VEHICULE_BAU", sizeof(req.msgId));
    req.displayPriority = 50;

    struct json_object* j_obj = encode_disp_m41_command_request(&req);
    if (!j_obj) {
        fprintf(stderr, "Erreur encodage JSON\n");
        return 1;
    }

    const char* json_str = json_object_to_json_string_ext(j_obj, JSON_C_TO_STRING_PRETTY);
    printf("JSON généré (CommandRequest) :\n%s\n", json_str);

    // ==== DECODAGE M41 ====
    printf("\n=========== DECODAGE M41 ===========\n");

    const char* json_input = "{ \
        \"msgId\": \"VEHICULE_BAU\", \
        \"displayPriority\": 50, \
        \"retStatus\": { \
            \"code\": \"RS_OK\", \
            \"rea\": \"MSG_1 deactivated\" \
        } \
    }";

    DispM41CommandResponse res;
    memset(&res, 0, sizeof(res));

    if (decode_disp_m41_command_response(json_input, &res) == 0) {
        printf("Structure décodée (CommandResponse) :\n");
        printf("  msgId : %s\n", res.msgId);
        printf("  displayPriority : %u\n", res.displayPriority);
        printf("  -> code : %s\n", res.retStatus.code);
        printf("  -> reason : %s\n", res.retStatus.rea);
    } else {
        fprintf(stderr, "Erreur de décodage JSON\n");
        json_object_put(j_obj);
        return 1;
    }

    json_object_put(j_obj);
    return 0;
}
