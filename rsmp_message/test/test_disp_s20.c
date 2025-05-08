#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disp_s20.h"
#include "disp_json_generic.h"

/**
 * @file test_disp_s20.c
 * @brief Test de sérialisation JSON pour DISP/S20 (Lecture des templates)
 */

int main() {
    // === ALLOCATION de la réponse DISP/S20 ===
    DispS20StatusResponse response;
    response.templateCount = 1;
    response.templates = calloc(response.templateCount, sizeof(TemplateObject));

    TemplateObject* tpl = &response.templates[0];
    strncpy(tpl->templateId, "TEMPLATE_OLD_SCHOOL", sizeof(tpl->templateId));
    tpl->readonly = true;
    tpl->zoneCount = 1;
    tpl->zones = calloc(tpl->zoneCount, sizeof(ZoneObject));

    // === Définition d’une zone ===
    ZoneObject* zone = &tpl->zones[0];
    strncpy(zone->zoneId, "LIGNE_1", sizeof(zone->zoneId));
    zone->colorCount = 1;
    strncpy(zone->supportedColors[0], "yellow", sizeof(zone->supportedColors[0]));

    zone->position.x = 1;
    zone->position.y = 1;
    zone->position.z = 0;

    strncpy(zone->zoneType, "Text", sizeof(zone->zoneType));

    // === Définition d’options de texte ===
    zone->textOptions = calloc(1, sizeof(TextOptions));
    strncpy(zone->textOptions->type, "TextLine", sizeof(zone->textOptions->type));
    strncpy(zone->textOptions->textColor, "yellow", sizeof(zone->textOptions->textColor));
    strncpy(zone->textOptions->backgroundColor, "black", sizeof(zone->textOptions->backgroundColor));
    strncpy(zone->textOptions->font, "5x7", sizeof(zone->textOptions->font));
    strncpy(zone->textOptions->horizontalAlign, "Center", sizeof(zone->textOptions->horizontalAlign));
    strncpy(zone->textOptions->verticalAlign, "Middle", sizeof(zone->textOptions->verticalAlign));
    strncpy(zone->textOptions->orientation, "LeftRightTopBottom", sizeof(zone->textOptions->orientation));

    // === SERIALISATION JSON ===
    struct json_object* j = encode_disp_s20_status_response(&response);
    if (j) {
        printf("========== DISP/S20 JSON ==========\n");
        printf("%s\n", json_object_to_json_string_ext(j, JSON_C_TO_STRING_PRETTY));
        json_object_put(j); // Libération JSON
    }

    // === LIBÉRATION MÉMOIRE ===
    free(zone->textOptions);
    free(tpl->zones);
    free(response.templates);

    return 0;
}
