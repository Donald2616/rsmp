#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "disp_m40.h"
#include "disp_json_generic.h"

int main() {
    // Création de la commande M40
    DispM40CommandRequest req = {
        .msgId = "VEHICULE_BAU",
        .displayBehavior = DISPLAY_BEHAVIOR_DROP,
        .maxWaitTime = 0,
        .displayDuration = 0,
        .displayPriority = 50,
        .dynamicData = ""
    };

    printf("========= ENCODAGE M40 =========\n");
    struct json_object* j_req = encode_disp_m40_command_request(&req);
    printf("JSON généré (CommandRequest) :\n%s\n", json_object_to_json_string_ext(j_req, JSON_C_TO_STRING_PRETTY));
    json_object_put(j_req);

    // Chaîne JSON simulée pour décodage
    const char* json_response = "{"
        "\"msgId\": \"VEHICULE_BAU\","
        "\"behaviorUsed\": \"Displayed\","
        "\"retStatus\": {"
            "\"code\": \"RS_OK\","
            "\"rea\": \"VEHICULE_BAU activated\""
        "}"
    "}";

    printf("\n========= DECODAGE M40 =========\n");
    DispM40CommandResponse res;
    if (decode_disp_m40_command_response(json_response, &res) == 0) {
        printf("Structure décodée (CommandResponse) :\n");
        printf("  msgId: %s\n", res.msgId);
        printf("  behaviorUsed: %s\n", res.behaviorUsed);
        printf("  -> code: %s\n", res.retStatus.code);
        printf("  -> reason: %s\n", res.retStatus.rea);
    } else {
        printf("Erreur de décodage JSON.\n");
    }

    return 0;
}
