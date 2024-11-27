#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

// Definição da struct com uma única declaração de float
typedef struct {
    float peso, altura, imc, taxaBasal, percentualGordura;
    float cintura, pescoco, quadril; // Novos campos para cálculo preciso
    int idade, objetivo;
    char sexo;
} Usuario;

// Função para calcular o IMC
float calcularIMC(float peso, float altura) {
    return peso / pow((altura / 100), 2);
}

// Função para calcular a Taxa Metabólica Basal
float calcularTaxaBasal(float peso, float altura, int idade, char sexo) {
    if (sexo == 'M' || sexo == 'm') {
        return 88.362 + (13.397 * peso) + (4.799 * altura) - (5.677 * idade);
    } else {
        return 447.593 + (9.247 * peso) + (3.098 * altura) - (4.330 * idade);
    }
}

// Função para calcular percentual de gordura corporal (Jackson e Pollock)
float calcularGorduraPrecisa(float cintura, float pescoco, float altura, char sexo, float quadril) {
    if (sexo == 'M' || sexo == 'm') {
        return 495 / (1.0324 - 0.19077 * log10(cintura - pescoco) + 0.15456 * log10(altura)) - 450;
    } else {
        return 495 / (1.29579 - 0.35004 * log10(cintura + quadril - pescoco) + 0.22100 * log10(altura)) - 450;
    }
}

// Função para capturar os dados de um usuário
void capturarDados(Usuario *usuario) {
    printf("Informe o seu peso (kg): ");
    while (scanf("%f", &usuario->peso) != 1 || usuario->peso <= 0) {
        printf("Por favor, insira um valor válido para o peso: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    printf("Informe a sua altura (cm): ");
    while (scanf("%f", &usuario->altura) != 1 || usuario->altura <= 0) {
        printf("Por favor, insira um valor válido para a altura: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    printf("Informe a sua idade (anos): ");
    while (scanf("%d", &usuario->idade) != 1 || usuario->idade <= 0) {
        printf("Por favor, insira um valor válido para a idade: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    do {
        printf("Informe o seu sexo (M para masculino, F para feminino): ");
        scanf(" %c", &usuario->sexo);
        while (getchar() != '\n'); // Limpa o buffer após o caractere
        if (usuario->sexo != 'M' && usuario->sexo != 'm' && usuario->sexo != 'F' && usuario->sexo != 'f') {
            printf("Entrada inválida. Por favor, digite 'M' ou 'F'.\n");
        }
    } while (usuario->sexo != 'M' && usuario->sexo != 'm' && usuario->sexo != 'F' && usuario->sexo != 'f');

    printf("Informe a medida da sua cintura (cm): ");
    while (scanf("%f", &usuario->cintura) != 1 || usuario->cintura <= 0) {
        printf("Por favor, insira um valor válido para a cintura: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    printf("Informe a medida do seu pescoço (cm): ");
    while (scanf("%f", &usuario->pescoco) != 1 || usuario->pescoco <= 0) {
        printf("Por favor, insira um valor válido para o pescoço: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    if (usuario->sexo == 'F' || usuario->sexo == 'f') {
        printf("Informe a medida do seu quadril (cm): ");
        while (scanf("%f", &usuario->quadril) != 1 || usuario->quadril <= 0) {
            printf("Por favor, insira um valor válido para o quadril: ");
            while (getchar() != '\n'); // Limpa o buffer
        }
    } else {
        usuario->quadril = 0; // Não necessário para homens
    }
}

// Função para calcular os resultados para um usuário
void calcularResultados(Usuario *usuario) {
    usuario->imc = calcularIMC(usuario->peso, usuario->altura);
    usuario->taxaBasal = calcularTaxaBasal(usuario->peso, usuario->altura, usuario->idade, usuario->sexo);
    usuario->percentualGordura = calcularGorduraPrecisa(usuario->cintura, usuario->pescoco, usuario->altura, usuario->sexo, usuario->quadril);
}

// Função para exibir o menu de escolhas
void exibirMenu(Usuario *usuario) {
    int opcao;

    do {
        printf("\n=== Menu de Resultados ===\n");
        printf("!!Lembre-se de procurar a ajuda de um especialista!!\n");
        printf("1 - Ver IMC (Índice de Massa Corporal)\n");
        printf("2 - Ver Taxa Metabólica Basal\n");
        printf("3 - Ver Percentual de Gordura Corporal\n");
        printf("4 - Ver todos os resultados\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        while (scanf("%d", &opcao) != 1) {
            printf("Opção inválida. Tente novamente: ");
            while (getchar() != '\n'); // Limpa o buffer
        }

        switch (opcao) {
            case 1:
                printf("\nSeu IMC é: %.2f\n", usuario->imc);
                break;
            case 2:
                printf("\nSua Taxa Metabólica Basal é: %.2f kcal/dia\n", usuario->taxaBasal);
                break;
            case 3:
                printf("\nSeu Percentual de Gordura Corporal é: %.2f%%\n", usuario->percentualGordura);
                break;
            case 4:
                printf("\n=== Resultados Completos ===\n");
                printf("IMC: %.2f\n", usuario->imc);
                printf("Taxa Metabólica Basal: %.2f kcal/dia\n", usuario->taxaBasal);
                printf("Percentual de Gordura Corporal: %.2f%%\n", usuario->percentualGordura);
                break;
            case 5:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    printf("\n=== Bem-vindo à Calculadora Natural! ===\n\n");

    int quantidade;
    printf("Quantas pessoas você deseja calcular? ");
    while (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
        printf("Por favor, insira um número válido: ");
        while (getchar() != '\n'); // Limpa o buffer
    }

    Usuario *usuarios = (Usuario *)malloc(quantidade * sizeof(Usuario));
    if (usuarios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }
    int i;
    for (i = 0; i < quantidade; i++) {
        printf("\n=== Dados do Usuário %d ===\n", i + 1);
        capturarDados(&usuarios[i]);
        calcularResultados(&usuarios[i]);
        exibirMenu(&usuarios[i]);
    }

    printf("\nObrigado por usar a Calculadora Natural! Lembre-se de sempre buscar orientação médica ou de um nutricionista.\n");

    free(usuarios);
    return 0;
}

