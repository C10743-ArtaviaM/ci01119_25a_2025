#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "requests.h"
#include <cjson/cJSON.h>

typedef struct {
    char name[100];
    char status[100];
    char species[100];
    char type[100];
    char gender[100];
    char origin_name[100];
    char location_name[100];
} Character;

void fetch_characters(const char *url) {
    req_init();  // Inicializa la librería

    RequestsHandler *req = req_get(NULL, url, "");
    if (req == NULL || req_get_status_code(req) != 200) {
        fprintf(stderr, "Error en la petición HTTP (%d)\n", req ? req_get_status_code(req) : -1);
        if (req) req_close_connection(&req);
        req_cleanup();
        return;
    }

    // Buffer para leer el cuerpo de la respuesta
    #define BUFFER_SIZE 65536
    char buffer[BUFFER_SIZE];
    int bytes_read = req_read_output_body(req, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        fprintf(stderr, "Error leyendo el cuerpo de la respuesta\n");
        req_close_connection(&req);
        req_cleanup();
        return;
    }
    buffer[bytes_read] = '\0';  // Terminar string

    cJSON *json = cJSON_Parse(buffer);
    if (!json) {
        fprintf(stderr, "Error al parsear JSON\n");
        req_close_connection(&req);
        req_cleanup();
        return;
    }

    cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    if (!cJSON_IsArray(results)) {
        fprintf(stderr, "Campo 'results' no es un arreglo\n");
        cJSON_Delete(json);
        req_close_connection(&req);
        req_cleanup();
        return;
    }

    cJSON *character_json;
    cJSON_ArrayForEach(character_json, results) {
        Character character;

        const cJSON *name = cJSON_GetObjectItemCaseSensitive(character_json, "name");
        const cJSON *status = cJSON_GetObjectItemCaseSensitive(character_json, "status");
        const cJSON *species = cJSON_GetObjectItemCaseSensitive(character_json, "species");
        const cJSON *type = cJSON_GetObjectItemCaseSensitive(character_json, "type");
        const cJSON *gender = cJSON_GetObjectItemCaseSensitive(character_json, "gender");

        cJSON *origin = cJSON_GetObjectItemCaseSensitive(character_json, "origin");
        cJSON *location = cJSON_GetObjectItemCaseSensitive(character_json, "location");

        strncpy(character.name, name && cJSON_IsString(name) ? name->valuestring : "(null)", sizeof(character.name));
        character.name[sizeof(character.name)-1] = '\0';
        strncpy(character.status, status && cJSON_IsString(status) ? status->valuestring : "(null)", sizeof(character.status));
        character.status[sizeof(character.status)-1] = '\0';
        strncpy(character.species, species && cJSON_IsString(species) ? species->valuestring : "(null)", sizeof(character.species));
        character.species[sizeof(character.species)-1] = '\0';
        strncpy(character.type, type && cJSON_IsString(type) ? type->valuestring : "", sizeof(character.type));
        character.type[sizeof(character.type)-1] = '\0';
        strncpy(character.gender, gender && cJSON_IsString(gender) ? gender->valuestring : "(null)", sizeof(character.gender));
        character.gender[sizeof(character.gender)-1] = '\0';

        const cJSON *origin_name_json = origin ? cJSON_GetObjectItemCaseSensitive(origin, "name") : NULL;
        strncpy(character.origin_name, origin_name_json && cJSON_IsString(origin_name_json) ? origin_name_json->valuestring : "(null)", sizeof(character.origin_name));
        character.origin_name[sizeof(character.origin_name)-1] = '\0';

        const cJSON *location_name_json = location ? cJSON_GetObjectItemCaseSensitive(location, "name") : NULL;
        strncpy(character.location_name, location_name_json && cJSON_IsString(location_name_json) ? location_name_json->valuestring : "(null)", sizeof(character.location_name));
        character.location_name[sizeof(character.location_name)-1] = '\0';

        printf("Name: %s\n", character.name);
        printf("Status: %s\n", character.status);
        printf("Species: %s\n", character.species);
        printf("Type: %s\n", *character.type ? character.type : "(none)");
        printf("Gender: %s\n", character.gender);
        printf("Origin: %s\n", character.origin_name);
        printf("Location: %s\n", character.location_name);
        printf("------------------------\n");
    }

    cJSON_Delete(json);
    req_close_connection(&req);
    req_cleanup();
}

int main() {
    const char *api_url = "https://rickandmortyapi.com/api/character";
    fetch_characters(api_url);
    return 0;
}
