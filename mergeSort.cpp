#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;




int LARGURA_JANELA = 1280;
int ALTURA_JANELA = 730;

void merge(int *arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}


void mergeSort(int *arr, int l, int r, sf::RenderWindow &janela, int TAMANHO_ARRAY, std::chrono::milliseconds velocidade)
{
    if (l < r)
    {

        sf::Font font;
        font.loadFromFile("OpenSans-Regular.ttf");
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, janela, TAMANHO_ARRAY, velocidade);
        mergeSort(arr, m + 1, r, janela, TAMANHO_ARRAY, velocidade);

        merge(arr, l, m, r);

        janela.clear();
        for (int i = 0; i < TAMANHO_ARRAY; ++i)
        {
            sf::RectangleShape retangulo(sf::Vector2f(LARGURA_JANELA / TAMANHO_ARRAY, arr[i] * ALTURA_JANELA / TAMANHO_ARRAY));
            retangulo.setPosition(i * LARGURA_JANELA / TAMANHO_ARRAY, ALTURA_JANELA - (arr[i] * ALTURA_JANELA / TAMANHO_ARRAY));
            retangulo.setFillColor(sf::Color(0, 0, 255));
            retangulo.setOutlineThickness(1.0f);
            retangulo.setOutlineColor(sf::Color::Black);
            janela.draw(retangulo);
            
            if (TAMANHO_ARRAY <= 70) {
                sf::Text numero;
                numero.setFont(font);
                numero.setCharacterSize(10);
                numero.setString(std::to_string(arr[i]));
                numero.setFillColor(sf::Color::White);
                numero.setPosition(retangulo.getPosition().x + 5, retangulo.getPosition().y - 20);
                janela.draw(numero);
            }
        }
        janela.display();
        std::this_thread::sleep_for(velocidade);
    }
}


void mergeSortComcor(int *arr, int l, int r, sf::RenderWindow &janela, int TAMANHO_ARRAY, std::chrono::milliseconds velocidade)
{
    if (l < r)
    {   
        sf::Font font;
        font.loadFromFile("OpenSans-Regular.ttf");
        int m = l + (r - l) / 2;

        mergeSortComcor(arr, l, m, janela, TAMANHO_ARRAY, velocidade);
        mergeSortComcor(arr, m + 1, r, janela, TAMANHO_ARRAY, velocidade);

        merge(arr, l, m, r);

        int valor_minimo = arr[l];
        int valor_maximo = arr[r];
        for (int i = l; i <= r; ++i)
        {
            if (arr[i] < valor_minimo)
                valor_minimo = arr[i];
            if (arr[i] > valor_maximo)
                valor_maximo = arr[i];
        }

        janela.clear(sf::Color(43, 66, 54));
        for (int i = 0; i < TAMANHO_ARRAY; ++i)
        {
            int intensidade = 255 * (arr[i] - valor_minimo) / (valor_maximo - valor_minimo);
            sf::Color cor(intensidade, intensidade, intensidade);
            sf::RectangleShape retangulo(sf::Vector2f(LARGURA_JANELA / TAMANHO_ARRAY, arr[i] * ALTURA_JANELA / TAMANHO_ARRAY));
            retangulo.setPosition(i * LARGURA_JANELA / TAMANHO_ARRAY, ALTURA_JANELA - (arr[i] * ALTURA_JANELA / TAMANHO_ARRAY));
            retangulo.setFillColor(cor);
            retangulo.setOutlineThickness(1.0f);
            retangulo.setOutlineColor(sf::Color::Black);
            janela.draw(retangulo);

            if (TAMANHO_ARRAY <= 70) {
                sf::Text numero;
                numero.setFont(font);
                numero.setCharacterSize(10);
                numero.setString(std::to_string(arr[i]));
                numero.setFillColor(sf::Color::White);
                numero.setPosition(retangulo.getPosition().x + 5, retangulo.getPosition().y - 20);
                janela.draw(numero);
            }
        }

        janela.display();
        std::this_thread::sleep_for(velocidade);
    }
}

void menu(int *fatz, sf::RenderWindow &janela, std::string mensagem){

    sf::Texture textura;

    if(!textura.loadFromFile("backgorund.png")){
        printf("Não foi possivel carregar o arquivo\n");
    }

    sf::Sprite img;

    img.setTexture(textura);

    sf::Font fonte;
    fonte.loadFromFile("OpenSans-Regular.ttf");

    sf::Text rotulo;
    rotulo.setFont(fonte);
    rotulo.setCharacterSize(40);
    rotulo.setString(mensagem);
    rotulo.setFillColor(sf::Color::Black);
    rotulo.setPosition(410, 250);

    sf::RectangleShape caixaTexto(sf::Vector2f(200, 40));
    caixaTexto.setFillColor(sf::Color::White);
    caixaTexto.setOutlineThickness(2);
    caixaTexto.setOutlineColor(sf::Color::Black);
    caixaTexto.setPosition(525, 350);

    sf::Text texto;
    texto.setFont(fonte);
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::Black);
    texto.setPosition(525, 350);

    sf::CircleShape botao(70);
    botao.setFillColor(sf::Color::Red);
    botao.setOutlineThickness(2);
    botao.setOutlineColor(sf::Color::Black);
    botao.setPosition(550, 400);

    int tamanhoMaximo = 500;

    bool concluido = false;
    while (!concluido) {
        sf::Event evento;
        while (janela.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                janela.close();
                exit(0);
            }
            if (evento.type == sf::Event::TextEntered) {
                if (evento.text.unicode == 13) { 
                    concluido = true;
                    break;
                }
                else if (evento.text.unicode == 8) { 
                    if (!texto.getString().isEmpty()) {
                        std::string str = texto.getString();
                        str.pop_back();
                        texto.setString(str);
                    }
                }
                else if (evento.text.unicode >= 48 && evento.text.unicode <= 57) { 
                    if (texto.getString().getSize() < 3) {
                        std::string str = texto.getString();
                        if (str.empty() && evento.text.unicode == 48) continue; 
                        str += static_cast<char>(evento.text.unicode);
                        if (std::stoi(str) <= tamanhoMaximo) {
                            texto.setString(str);
                        }
                    }
                }
            }
            if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f posicaoMouse = janela.mapPixelToCoords(sf::Vector2i(evento.mouseButton.x, evento.mouseButton.y));
                if (botao.getGlobalBounds().contains(posicaoMouse)) {
                    concluido = true;
                    break;
                }
            }
        }

        janela.clear();
        janela.draw(img);
        janela.draw(rotulo);
        janela.draw(caixaTexto);
        janela.draw(texto);
        janela.draw(botao);
        janela.display();
    }

    *fatz = std::stoi(texto.getString().toAnsiString());

}






int main()
{
    sf::RenderWindow janela(sf::VideoMode(LARGURA_JANELA, ALTURA_JANELA), "Merge Sort");

    int TAMANHO_ARRAY = 10;
    int velocidade;

    // scanf("%d", &TAMANHO_ARRAY);

    menu(&TAMANHO_ARRAY, janela, "Digite o tamanho do vetor:");
    menu(&velocidade, janela, "Digite a atualizacao de cada etapa em ms:");

    std::chrono::milliseconds velocidadedef(velocidade);

    int arr[TAMANHO_ARRAY];

    for (int i = 0; i < TAMANHO_ARRAY; ++i)
        arr[i] = i + 1;

    srand(time(NULL));
    for (int i = TAMANHO_ARRAY - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }





    while(janela.isOpen()){

        sf::Event evento;

        while(janela.pollEvent(evento)){

            switch(evento.type){

                case sf::Event::Closed:

                    janela.close();

                    break;


                case sf::Event::KeyPressed:


                    switch(evento.key.code){

                        case sf::Keyboard::A:

                            mergeSortComcor(arr, 0, TAMANHO_ARRAY - 1,janela, TAMANHO_ARRAY, velocidadedef);

                            break;

                        case sf::Keyboard::D:

                            mergeSort(arr, 0, TAMANHO_ARRAY - 1,janela, TAMANHO_ARRAY, velocidadedef);

                            break;

                            } 

                        break;

                        }

            }

    }

    return 0;
}
