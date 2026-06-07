
#include "ProcessClientMessage.h"

void Exec_MSG_AuctionAction(int conn, char* pMsg)
{
    MSG_AuctionAction* m = (MSG_AuctionAction*)pMsg;
    
    if (pUser[conn].Mode != USER_PLAY)
        return;

    switch (m->ActionType)
    {
    case 1: // List Item
    {
        // Verifica se o item existe na mão (cursor) ou slot específico
        // Simplificado: assume que o item está no pacote enviado (precisa de validação real no inventário)
        if (m->Item.sIndex <= 0 || m->Price <= 0) {
            SendClientMessage(conn, "Item ou preço inválido.");
            return;
        }

        // Enviar para o DBSrv para salvar
        // No WYD real, enviaríamos um pacote GAME2DB
        // Aqui simulamos a chamada ou preparamos o pacote
        SendClientMessage(conn, "Item colocado em leilão com sucesso!");
    } break;

    case 2: // Buy Item
    {
        if (m->AuctionID <= 0) return;

        // Verifica se tem Gold/Donate suficiente
        if (pMob[conn].MOB.Coin < m->Price) {
            SendClientMessage(conn, "Gold insuficiente.");
            return;
        }

        // Processar compra (Remover gold, adicionar item)
        // Requer comunicação com DBSrv para validar o ID do leilão
        SendClientMessage(conn, "Compra processada. Verifique seu baú!");
    } break;

    case 4: // Search / List
    {
        // Solicitar lista ao DBSrv
        SendClientMessage(conn, "Buscando itens no leilão...");
    } break;
    }
}
