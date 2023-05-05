#include <stdio.h>
#include <ulfius.h>
#include <string.h>
#include <jansson.h>
#include <pthread.h>
#include "utils.h"


#define PORT 8080



int response_json_get_saldo (const struct _u_request * request, struct _u_response * response, void * user_data) {
  
  /**
   *  TODO Aqui efetuar a chamada nas rotinas do CORE e com o retorno do Core gerar arquivo JSON
   * com o conteúdo para ser entregue pelo REST Server.
   * 
  */
  ulfius_set_string_body_response(response, 200, getMockData());
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

  ulfius_set_string_body_response(response, 200, getMockData());

  o_free(post_params);


  return U_CALLBACK_CONTINUE; 
}
void *run(void *threadarg) {
  struct _u_instance instance;

  
  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Erro na inicialização da instância, abortando\n");
    
  }

  ulfius_add_endpoint_by_val(&instance, "GET", "/contacorrente/saldo", NULL, 0, &response_json_get_saldo, NULL);
  ulfius_add_endpoint_by_val(&instance, "POST", "/contacorrente/", NULL, 0, &response_json_post_saldo, NULL);

   if (ulfius_start_framework(&instance) == U_OK) {
    printf("RESTSicredi em C atendendo na porta %d\n", instance.port);
    int character = getchar();
    while(character != -1 ){
      character = getchar();
      printf("Para parar o servidor RESTSicredi pressionar Control + C");
    }

  } else {
    fprintf(stderr, "Error inicializando o RESTServer\n");
  }
  printf("Fim do RESTServer\n");

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
  
}
int main(void) {
  pthread_t thread;
  pthread_create(&thread, NULL, run, NULL);
  pthread_join(thread, NULL);
  return 0;
}