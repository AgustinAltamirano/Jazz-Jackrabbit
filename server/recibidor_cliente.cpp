#include "recibidor_cliente.h"

RecibidorCliente::RecibidorCliente(ProtocoloServidor &protocolo) :
        protocolo(protocolo) {}


void RecibidorCliente::run() {
    try {
        while (sigo_vivo) {
            protocolo.recibir_mensaje();
            sigo_vivo = protocolo.sigue_vivo();
        }
    } catch (const std::exception &err) {
        if (sigo_vivo) {
            std::cerr << "Excepcion capturada: " << err.what() << "\n";
        }
    }
}


bool RecibidorCliente::sigue_vivo() {
    return sigo_vivo;
}

void RecibidorCliente::kill() {
    sigo_vivo = false;
}

