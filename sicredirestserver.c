#include <stdio.h>
#include <ulfius.h>

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

int response_json_saldo (const struct _u_request * request, struct _u_response * response, void * user_data) {
  
  /**
   *  TODO Aqui efetuar a chamada nas rotinas do CORE e com o retorno do Core gerar arquivo JSON
   * com o conteúdo para ser entregue pelo REST Server.
   * 
  */
  ulfius_set_string_body_response(response, 200, getData("./responses/data.json"));
  return U_CALLBACK_CONTINUE;
}

int main(void) {
  struct _u_instance instance;

  
  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Erro na inicialização da instância, abortando\n");
    return(1);
  }

  ulfius_add_endpoint_by_val(&instance, "GET", "/contacorrente/saldo", NULL, 0, &response_json_saldo, NULL);

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
