#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Lista circular: o ultimo elemento aponta para o primeiro
// Lista duplamente encadeada: todo nó aponta para o anterior e para o próximo (buble sort)

// LISTA DUPLAMENTE ENCADEADA:

// Estrutura de um nó:
// Todo nó aponta para o próximo nó (ptrNext)
// Todo nó aponta para o nó anterior (ptrPrev)
typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void insertBefore(Node*, int);
void deleteNode(Node**, Node*);
void displayList(Node*);
Node* searchNodebyValue(Node*, int);
void deleteNodebyValue(Node*, int);

int main()
{
    Node* head = nullptr;
    displayList(head);
    cout << "=======================" << endl;
    cout << "Inserindo no final da lista" << endl;
    insertEnd(&head,0);
    insertEnd(&head,1);
    insertEnd(&head,3);
    insertEnd(&head,7);
    insertEnd(&head,10);
    insertEnd(&head,10);
    insertEnd(&head,13);
    displayList(head);
    cout << "=======================" << endl;
    cout << "Inserindo no comeco da Lista" << endl;
    insertFront(&head,-1);
    insertFront(&head,-2);
    displayList(head);
    cout << "=======================" << endl;
    cout << "Inserindo depois de localizacao passada" << endl;
    insertAfter(head,-2); // Inserindo depois da primeira posição
    insertAfter(head->ptrNext->ptrNext,15); // Inserindo depois da terceira posição
    displayList(head);
    cout << "=======================" << endl;
    cout << "Deletando nos: " << endl;
    deleteNode(&head, head); // Deletando primeiro nó
    deleteNode(&head, head->ptrNext); // Deletando segundo nó
    displayList(head);
    cout << "=======================" << endl;
    cout << "Inserindo antes de localizacao passada" << endl;
    insertBefore(head->ptrNext,61); // Inserindo antes do segundo elemento
    insertBefore(head->ptrNext->ptrNext,12); // Inserindo antes do terceiro elemento
    displayList(head);
    cout << "=======================" << endl;
    cout << "Deletando no por valor" << endl;
    deleteNodebyValue(head, 89); // 89 não está na lista (Caso especial)
    deleteNodebyValue(head, 61); 
    deleteNodebyValue(head, 10); 

    displayList(head);

    return 0;
}

Node* createNode(int iPayload)
{
    // Essa função cria um novo nó

    // Alocando memória para um nó
    Node* temp = (Node*) malloc(sizeof(Node));
    
    // Carga do nó
    temp -> iPayload = iPayload;
    
    // Inicializando nó apontando para nulo (Sem nós na frente e na traseira)
    temp -> ptrNext = nullptr;
    temp -> ptrPrev = nullptr;
    
    return temp;
}

void displayList(Node* node)
{
    // Essa função printa a lista duplamente encadeada

    // Caso não existam nós na lista
    if (node == nullptr)
    {
        cout << "Lista vazia: Não é possível realizar displayList" << endl;
        return; 
    }
    
    // Caso o nó passado estiver no meio o no final da lista
    if  (node -> ptrPrev != nullptr)
    {
        cout << "Meio ou Fim da Lista: Não é possível realizar displayList" << endl;
        return;
    }
    
    // Caso o nó passado seja o primeiro elemento da lista
    Node* temp = node;
     
    cout << "Payload: ";
    
    // Print de todos os elementos da lista
    while(temp != nullptr)
    {
        cout << temp -> iPayload<< " ";
        temp = temp -> ptrNext;
    }
    
    cout << endl;
}

void insertFront(Node** head, int iPayload)
{
    // Essa função insere um nó no início de uma lista duplamente encadeada

    Node* newNode = createNode(iPayload);
    // newNode->ptrPrev = nullptr; (Cuidado Dobrado, não é necessário nesse caso)
    
    // Caso exista pelo menos um nó na lista
    if (*head != nullptr)
    {
        (*head)->ptrPrev = newNode;
        newNode->ptrNext = (*head);
        (*head) = newNode;
        
        return;
    }
    
    // Caso não existam nós na lista
    (*head) = newNode;
}

void insertEnd(Node** head, int iPayload)
{
    // Essa função inserre um novo nó no final da lista

    Node* newNode = createNode(iPayload);   
    //newNode->ptrNext = nullptr;

    // Caso a lista seja nula, inserimos um novo nó no final passado
    if (*head == nullptr)
    {
        //newNode->ptrPrev = nullptr;
        (*head) = newNode;
        return;
    }

    // Caso a lista não seja nula
    Node* temp = (*head);

    // Percorremos a lista até seu fim (ptrNext do último nó é nulo)
    while(temp->ptrNext != nullptr)
    {
        temp = temp->ptrNext;
    }

    // Temos agora o último nó da lista

    // newNode aponta para o fim da Lista
    newNode->ptrPrev = temp;

    // Antigo elemento aponta para o novo nó
    temp->ptrNext = newNode; 
}


void insertAfter(Node* ptrLocation, int iPayload)
{
    // Essa função insere um nó logo após um nó passado para a função

    // Caso a localização seja inválida
    if (ptrLocation == nullptr)
    {
        cout << "Location é NULL." << endl; 
        return;
    }
    
    // Corrigir nó a ser inserido
    Node* newNode = createNode(iPayload);
    newNode->ptrNext = ptrLocation->ptrNext;
    newNode->ptrPrev = ptrLocation;
    
    // Corrigir o ponto de inserção
    ptrLocation->ptrNext = newNode;
    
    // Caso exista elemento na frente do elemento adicionado
    if (newNode->ptrNext != nullptr)
    {
        // O nó da frente de newNode aponta para trás dele (O próprio newNode)
        newNode->ptrNext->ptrPrev = newNode;
    }
}

void insertBefore(Node* ptrLocation, int iPayload)
{
    // Essa função insere um nó logo antes de um nó passado para a função

    // Caso a localização seja inválida
    if (ptrLocation == nullptr)
    {
        cout << "Location é NULL." << endl; 
        return;
    }

    // Corrigir nó a ser inserido
    Node* newNode = createNode(iPayload);
    newNode->ptrNext = ptrLocation;
    newNode->ptrPrev = ptrLocation->ptrPrev;

    // Corrigir o ponto de inserção
    ptrLocation->ptrPrev = newNode;

    // Caso exista elemento na atrás do elemento adicionado
    if (newNode->ptrPrev != nullptr)
    {
        // O nó atrás de newNode aponta para frente dele (O próprio newNode)
        newNode->ptrPrev->ptrNext = newNode;
    }
}

void deleteNode(Node** head, Node* ptrDelete)
{
    // Essa função deleta um nó específico da lista

    // Caso a lista seja nulo ou o nó seja nulo
    if (*head == nullptr || ptrDelete == nullptr)   
    {
        cout << "Não foi possível remover." << endl;
        return;
    }
    
    // Caso o ptrDelete seja o primeiro elemento da lista
    if (*head == ptrDelete) 
        (*head) = ptrDelete->ptrNext;
    
    // Se o ptrDelete não é o último nó
    if (ptrDelete->ptrNext != nullptr) 
        ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev; 
    
    // Se o ptrDelete não é o primeiro nó
    if (ptrDelete->ptrPrev != nullptr)
        ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;
    
    free(ptrDelete);
}

Node* searchNodebyValue(Node* head, int iPayload)
{
    // Caso não tenha elementos na lista
    if (head == nullptr)
    {
        cout << "Lista vazia" << endl;
        return nullptr;
    }

    Node* temp = head;

    // Percorrendo toda a lista até que ela seja nula
    while(temp != nullptr)
    {
        // Caso o valor for encontrado, é retornado o endereço desse nó
        if (temp->iPayload == iPayload)
            return temp;

        temp = temp->ptrNext;
    }

    // Caso o nó não tenha a carga, se retorna nullptr
    return temp;
}

void deleteNodebyValue(Node* head, int iPayload)
{
    // Essa função deleta o primeiro nó de acordo com a carga passada

    // Caso a lista seja vazia 
    if (head == nullptr)
    {
        cout << "Lista vazia" << endl;
        return;
    }

    // Deletando o nó de acordo com a carga passada (caso não existir, não se altera a lista)
    deleteNode(&head, searchNodebyValue(head, iPayload));
}

// Exercício 1. Elaborar a função void insertBefore(Node*, int)
// Exercício 2. Elaborar a função void deleteNodebyValue(Node*, int)
// Exercício 3. Elaborar a função Node* searchNodebyValue(Node*, int)
