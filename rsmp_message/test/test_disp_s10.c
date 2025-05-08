#include <stdio.h>
#include <string.h>
#include "disp_s10.h"
#include "disp_json_generic.h"

int main() {
    DispS10StatusResponse res = {
        .displayType = "Mixed",
        .templateType = "Static",
        .minDisplayTime = 1000,
        .maxObjectIdSize = 16,
        .maxSupportedTemplate = 2,
        .maxSupportedZone = 5,
        .maxSupportedSequence = 5,
        .maxSupportedAnimation = 5,
        .maxSupportedAvailableMsg = 5,
        .maxSupportedDisplayPool = 255,
        .maxScrollSpeed = 15,
        .size = { .width = 340, .height = 80 },
        .textDisplayable = 1,
        .predefinedGroupCount = 1
    };

    static PredefinedGroupObject groups[1];
    strcpy(groups[0].predefinedGroupId, "PDEF_FLASH");
    groups[0].enumCount = 2;
    strcpy(groups[0].supportedEnum[0], "OFF");
    strcpy(groups[0].supportedEnum[1], "FLASH_ON");

    res.predefinedGroups = groups;

    struct json_object* json = encode_disp_s10_status_response(&res);
    printf("%s\n", json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY));
    json_object_put(json);

    return 0;
}
