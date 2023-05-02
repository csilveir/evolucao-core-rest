#include <stdio.h>
#include <ulfius.h>
#include <string.h>
#include <jansson.h>


#define PORT 8080

char* getData(char* directory) {

    char * buffer = 0;
    long length;
    FILE * file = fopen(directory,"rb");

    if (file)
        {
            fseek (file, 0, SEEK_END);
            length = ftell (file);
            fseek (file, 0, SEEK_SET);
            buffer = malloc (length);
            if (buffer)
            {
                fread (buffer, 1, length, file);
            }
            fclose (file);
        }

    return buffer;

}

char * print_map(const struct _u_map * map) {
  char * line, * to_return = NULL;
  const char **keys, * value;
  int len, i;
  if (map != NULL) {
    keys = u_map_enum_keys(map);
    for (i=0; keys[i] != NULL; i++) {
      value = u_map_get(map, keys[i]);
      len = snprintf(NULL, 0, "key is %s, value is %s", keys[i], value);
      line = o_malloc((size_t)(len+1));
      snprintf(line, (size_t)(len+1), "key is %s, value is %s", keys[i], value);
      if (to_return != NULL) {
        len = (int)(o_strlen(to_return) + o_strlen(line) + 1);
        to_return = o_realloc(to_return, (size_t)(len+1));
        if (o_strlen(to_return) > 0) {
          strcat(to_return, "\n");
        }
      } else {
        to_return = o_malloc((o_strlen(line) + 1));
        to_return[0] = 0;
      }
      strcat(to_return, line);
      o_free(line);
    }
    return to_return;
  } else {
    return NULL;
  }
}

int response_json_get_saldo (const struct _u_request * request, struct _u_response * response, void * user_data) {
  
  /**
   *  TODO Aqui efetuar a chamada nas rotinas do CORE e com o retorno do Core gerar arquivo JSON
   * com o conteúdo para ser entregue pelo REST Server.
   * 
  */
  ulfius_set_string_body_response(response, 200, getData("./responses/data.json"));
  return U_CALLBACK_CONTINUE;
}

int response_json_post_saldo (const struct _u_request * request, struct _u_response * response, void * user_data) {

  (void)(user_data);

  printf("POST binary_body_length: %zu\n", request->binary_body_length);




  char * post_params = print_map(request->map_post_body);
  json_t * json_nb_sheep = ulfius_get_json_body_request(request, NULL), * json_body = NULL;

 // Pegandos os atributos da requisição.

  printf("id: %f \n",json_number_value(json_object_get(json_nb_sheep,"id")));
  printf("name: %s \n",json_string_value(json_object_get(json_nb_sheep,"name")));

  ulfius_set_string_body_response(response, 200, getData("./responses/data.json"));

  o_free(post_params);


  return U_CALLBACK_CONTINUE; 
}
int main(void) {
  struct _u_instance instance;

  
  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Erro na inicialização da instância, abortando\n");
    return(1);
  }

  ulfius_add_endpoint_by_val(&instance, "GET", "/contacorrente/saldo", NULL, 0, &response_json_get_saldo, NULL);
  ulfius_add_endpoint_by_val(&instance, "POST", "/contacorrente/", NULL, 0, &response_json_post_saldo, NULL);

   if (ulfius_start_framework(&instance) == U_OK) {
    printf("RESTServer Sicredi em C atendendo na porta %d\n", instance.port);

    getchar();
  } else {
    fprintf(stderr, "Error inicializando o RESTServer\n");
  }
  printf("Fim do RESTServer\n");

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);

  return 0;
}
