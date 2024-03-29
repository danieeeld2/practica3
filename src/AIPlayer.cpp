#include "AIPlayer.h"
#include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move()
{
    cout << "Realizo un movimiento automatico" << endl;

    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color &c_piece, int &id_piece, int &dice) const
{
    // switch(id){
    //     case 0:
    //         thinkAleatorio(c_piece,id_piece,dice);
    //         break;
    //     case 1:
    //         thinkAleatorioMasInteligete(c_piece,id_piece,dice);
    //         break;
    //     case 2:
    //         thinkFichasMasAdelante(c_piece,id_piece,dice);
    //         break;
    //     case 3:
    //         thinkMejorOpcion(c_piece,id_piece,dice);
    //         break;
    // }
    double alpha = menosinf;
    double beta = masinf;
    // double valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    double valor;

    switch(id){
        case 0:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
            break;
        case 1:
            cout << "Es la buena" << endl;
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, PorFavorFunciona);
            break;
        case 2:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, Heuristica_Chorra);
            break;
    }

    // valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, PorFavorFunciona);
    
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;
}

void AIPlayer::thinkAleatorio(color &c_piece, int &id_piece, int &dice) const
{
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente
    // como lo que se muestran al final de la función.

    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores,
    // respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(c_piece, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if (current_pieces.size() > 0)
    {
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    else
    {
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
    }

    /*
    // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
    valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del agente para usar una u otra.
    switch(id){
        case 0:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
            break;
        case 1:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, MiValoracion1);
            break;
        case 2:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, MiValoracion2);
            break;
    }
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    */
}

void AIPlayer::thinkAleatorioMasInteligete(color &c_piece, int &id_piece, int &dice) const
{
    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);

    // En vez de elegir un dado al azar, miro primero cuáles tienen fichas que se puedan mover
    vector<int> current_dices_que_pueden_mover_ficha;
    for (int i = 0; i < current_dices.size(); i++)
    {
        // Se obtiene el vector de fichas que se pueden mover para el dado elegido
        current_pieces = actual->getAvailablePieces(c_piece, current_dices[i]);

        // Si se pueden mover fichas para el dado actual, lo añado al vector de dados que pueden mover fichas
        if (current_pieces.size() > 0)
        {
            current_dices_que_pueden_mover_ficha.push_back(current_dices[i]);
        }
    }

    // Si no tengo ningún dado que pueda mover fichas, paso de turno con un dado al azar
    if (current_dices_que_pueden_mover_ficha.size() == 0)
    {
        dice = current_dices[rand() % current_dices.size()];
        id_piece = SKIP_TURN;
    }
    else
    {
        // En caso contrario elijo un dado de forma aleatoria entre los que pueden mover ficha
        dice = current_dices_que_pueden_mover_ficha[rand() % current_dices_que_pueden_mover_ficha.size()];

        // Se obtiene el vector de fichas que se puedan mover para el dado elegido
        current_pieces = actual->getAvailablePieces(c_piece, dice);

        // Muevi una ficha al azar entre las que se puedan mover
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
}

void AIPlayer::thinkFichasMasAdelante(color &c_piece, int &id_piece, int &dice) const
{
    // Elijo el dado haciendo lo mismo que el jugador anterior
    thinkAleatorioMasInteligete(c_piece, id_piece, dice);
    // Tras llamar a esta función, ya tengo en dice el número de dado que quiero usar
    // Ahora, en vez de mover una ficha al azar, voy a mover la que esté más adelantada
    // es decir, la que esté mas cercana a la meta

    vector<int> current_pieces = actual->getAvailablePieces(c_piece, dice);

    int id_ficha_mas_adelantada = -1;
    int min_distancia_meta = 9999;
    for (int i = 0; i < current_pieces.size(); i++)
    {
        // distanceToGoal(color, id) devuelve ña distancia a la meta de la ficha [id] del color que le indique
        int distancia_meta = actual->distanceToGoal(c_piece, current_pieces[i]);
        if (distancia_meta < min_distancia_meta)
        {
            min_distancia_meta = distancia_meta;
            id_ficha_mas_adelantada = current_pieces[i];
        }
    }

    // Si no he encontrado ninguna ficha, paso turno
    if (id_ficha_mas_adelantada == -1)
    {
        id_piece = SKIP_TURN;
    }
    else
    { // En caso contrario, moveré la más adelantada
        id_piece = id_ficha_mas_adelantada;
    }
}

void AIPlayer::thinkMejorOpcion(color &c_piece, int &id_piece, int &dice) const
{
    // Vamos a mirar todos los posibles movimientos del jugador actual accediendo a los hijos del estado actual

    // generateNextMove va iterando sobre cada hijo. Le paso la acción del último movimiento sobre
    // el que he iterado y me devolverá el siguiente. Inicialmente, cuando aún no he hecho ningún
    // movimiento, lo inicializo así:
    color last_c_piece = none; // El color de la última ficha que se movió
    int last_id_piece = -1;    // El ide de la última ficha que se movió
    int last_dice = -1;        // El dado que se usó en el último movimiento

    // Cuando ya he recorrido todos los hijos, la función devuelve el estado actual. De esta forma puedo saber
    // cuando paro de iterar

    Parchis siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);

    bool me_quedo_con_esta_accion = false;

    while (!(siguiente_hijo == *actual) && !me_quedo_con_esta_accion)
    {
        if (siguiente_hijo.isEatingMove() or                                            // Si con este movimiento como ficha
            siguiente_hijo.isGoalMove() or                                              // Si con este movimiento llego a la meta
            (siguiente_hijo.gameOver() and siguiente_hijo.getWinner() == this->jugador) // Si con este movimiento gano la partida
        )
        {
            // Me quedo con la acción actual
            me_quedo_con_esta_accion = true;
        }
        else
        {
            // Genero el siguiente hijo
            siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);
        }
    }

    // Si he encontrado una acción que me interesa, la guardo en las variables por referencia
    if (me_quedo_con_esta_accion)
    {
        c_piece = last_c_piece;
        id_piece = last_id_piece;
        dice = last_dice;
    }
    else
    {
        // Si no, muevo la ficha más adelantada como antes
        thinkFichasMasAdelante(c_piece, id_piece, dice);
    }
}

double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.

    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

double AIPlayer::Poda_AlfaBeta(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, double alpha, double beta, double (*heuristic)(const Parchis &, int)) const
{
    if (profundidad == profundidad_max || actual.gameOver())
    {
        return heuristic(actual, jugador);
    }

    color last_c = none;
    int last_piece = -1;
    int last_dice = -1;
    Parchis hijo = actual.generateNextMoveDescending(last_c, last_piece, last_dice);

    if (actual.getCurrentPlayerId() == jugador)
    {
        while (!(hijo == actual))
        {
            auto valor_poda = Poda_AlfaBeta(hijo, jugador, profundidad + 1, profundidad_max, last_c, last_piece, last_dice, alpha, beta, heuristic);
            if (alpha < valor_poda)
            {
                alpha = valor_poda;
                if (profundidad == 0)
                {
                    c_piece = last_c;
                    id_piece = last_piece;
                    dice = last_dice;
                }
            }

            if (beta <= alpha)
                break;

            hijo = actual.generateNextMoveDescending(last_c, last_piece, last_dice);
        }

        return alpha;
    }
    else
    {
        while (!(hijo == actual))
        {
            auto valor_poda = Poda_AlfaBeta(hijo, jugador, profundidad + 1, profundidad_max, last_c, last_piece, last_dice, alpha, beta, heuristic);
            if (valor_poda < beta)
                beta = valor_poda;

            if (beta <= alpha)
                break;

            hijo = actual.generateNextMoveDescending(last_c, last_piece, last_dice);
        }
        return beta;
    }
}

double AIPlayer::Heuristica_Chorra(const Parchis &estado, int jugador){
    auto mis_colores = estado.getPlayerColors(jugador);
    double mi_suma = 0.0;
    for(const auto &c:mis_colores){
        auto piezas = estado.getBoard().getPieces(c);
        for(const auto &pieza : piezas){
            mi_suma += estado.distanceToGoal(c,pieza);
        }
    }

    return -mi_suma;
}

double AIPlayer::PorFavorFunciona(const Parchis &estado, int jugador){
    int oponente = (jugador+1)%2;
    auto mis_colores = estado.getPlayerColors(jugador);
    auto colores_oponente = estado.getPlayerColors(oponente);
    double heuristica = 0.0;

    for(int i=0;i<mis_colores.size();i++){
        double heuristica_color = 0.0;
        heuristica_color -= 15000*estado.piecesAtHome(mis_colores[i]);

        for(int j=0;j<num_pieces;j++){
            auto mi_ficha = estado.getBoard().getPiece(mis_colores[i],j);
            if(estado.isSafeBox(mi_ficha)){
                heuristica_color += 8000;
            }else{
                auto distancia_a_meta = estado.distanceToGoal(mis_colores[i],j);
                heuristica_color += distancia_a_meta > 7 ? -500*distancia_a_meta : 7000;
            }
        }

        heuristica += heuristica_color*1000;
    }

    for(int i=0;i<colores_oponente.size();i++){
        double heuristica_color_oponente = 0.0;
        heuristica_color_oponente += 15000*estado.piecesAtHome(colores_oponente[i]);

        for(int j=0;j<num_pieces;j++){
            auto ficha_oponente = estado.getBoard().getPiece(colores_oponente[i],j);
            auto distancia = estado.distanceToGoal(colores_oponente[i],j);
            heuristica_color_oponente += distancia > 7 ? 5000*distancia : -1000;
        }

        heuristica += heuristica_color_oponente*1000;
    }

    return heuristica;
}
