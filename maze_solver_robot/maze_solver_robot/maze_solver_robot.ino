        /* Algoritmo Daileon – Resolvedor de Labirintos
    Criado por: Jaspion Lopes de Freitas
    Curso: Ciência da Computação
    Instituição: Faculdade Pitágoras Votorantim-Sorocaba
    */

    // definições e declarações de variáveis do código do robô resolvedor de labirintos;
    
    #define vel_motor_esq 10  // controla velocidade do motor esquerdo;
    #define vel_motor_dir 11  // controla velocidade do motor direito;         
    #define e1 8  // controla sentido de rotação do motor esquerdo;
    #define e2 9  // controla sentido de rotação do motor esquerdo;
    #define d1 12  //controla sentido de rotação do motor direito;
    #define d2 7  // controla sentido de rotação do motor direito;
 
    int trigger_frente = A4; // controla o impulso enviado do sensor da frente
    int echo_frente = A5; // controla o impulso recebido do sensor da frente
    
    int trigger_esq = A2;// controla o impulso enviado do sensor da frente
    int echo_esq = A3;// controla o impulso recebido do sensor da frente
    
    int trigger_dir = A0;// controla o impulso enviado do sensor da frente
    int echo_dir = A1;// controla o impulso recebido do sensor da frente
    
    // configuração dos tipos de entrada das variáveis declaradas;    
    void setup()
    {
        pinMode(trigger_frente, OUTPUT); // saída de sinal do arduino do trigger_frente
        pinMode(echo_frente, INPUT);// entrada de sinal do arduino do echo_frente
        
        pinMode(trigger_esq, OUTPUT);// saída de sinal do arduino do trigger_frente
        pinMode(echo_esq, INPUT);// entrada de sinal do arduino do echo_frente        
        
        pinMode(trigger_dir, OUTPUT);// saída de sinal do arduino do trigger_frente
        pinMode(echo_dir, INPUT);// entrada de sinal do arduino do echo_frente
       
        pinMode(vel_motor_esq, OUTPUT);// saída de sinal do arduino da velocidade do motor esquerdo
        pinMode(vel_motor_dir, OUTPUT);// saída de sinal do arduino da velocidade do motor direito
     
        pinMode(e1, OUTPUT);// saída de sinal do arduino do controle do sentido de rotação do motor esquerdo
        pinMode(e2, OUTPUT);// saída de sinal do arduino do controle do sentido de rotação do motor esquerdo
        pinMode(d1, OUTPUT);// saída de sinal do arduino do controle do sentido de rotação do motor direito
        pinMode(d2, OUTPUT);// saída de sinal do arduino do controle do sentido de rotação do motor direito       
        delay(5000);
    }
    
    // código em repetição infinita do projeto;
    void loop()
    {
     // declaração de variáveis utilizadas para controle do projeto;
     long duracao_frente, duracao_esq, duracao_dir, direita, esquerda, frente; 
     
     
     digitalWrite(trigger_frente, LOW);  // é declarada as respectivas entradas e saídas de sinal do
     delayMicroseconds(2);               // sensor ultrassônico e armazenada pela variável do sensor
     digitalWrite(trigger_frente, HIGH); // que converte a velocidade do som que é de 340 m/s ou  
     delayMicroseconds(5);               // 29 microsegundos por centímetro, como o sinal vai e volta
     digitalWrite(trigger_frente, LOW);  // esse tempo é a metade sendo sensor= tempo/29/2 ;
     duracao_frente = pulseIn(echo_frente, HIGH); // assim segue também nos outros dois sensores .
     frente = duracao_frente/29/2;
    
     digitalWrite(trigger_esq, LOW);
     delayMicroseconds(2);
     digitalWrite(trigger_esq, HIGH);
     delayMicroseconds(5);
     digitalWrite(trigger_esq, LOW); 
     duracao_esq = pulseIn(echo_esq, HIGH);
     esquerda = duracao_esq/29/2;
    
     digitalWrite(trigger_dir, LOW);
     delayMicroseconds(2);
     digitalWrite(trigger_dir, HIGH);
     delayMicroseconds(5);
     digitalWrite(trigger_dir, LOW); 
     duracao_dir = pulseIn(echo_dir, HIGH);
     direita = duracao_dir/29/2; 
     
     analogWrite(vel_motor_esq, 0);  //bloco para inicializar as entradas com pulso 0 ou desligado;
     analogWrite(vel_motor_dir, 0); //
     analogWrite(e1, 0);            //
     analogWrite(e2, 0);            //  
     analogWrite(d1, 0);            //
     analogWrite(d2, 0);            //
     
       if(frente >8) // se caso houver caminho livre a frente ele segue esta lógica abaixo:
         {  
           // o uso dos quatro if´s abaixo dentro deste if são para o controle da dirigibilidade do robô,
           // a fim de mantê-lo seguindo a parede direita em linha reta;  
           
           if(direita >7 && direita< 13) // se caso a distância da parede a direita estiver entre 9 e 12 cm, o robô se
                                         // mantém em linha reta;
             {               
               analogWrite(vel_motor_esq, 120);
               analogWrite(vel_motor_dir, 150);
           
               analogWrite(e1, 255);
               analogWrite(e2, 0);
               analogWrite(d1, 0);
               analogWrite(d2, 255);                                                        
             }
         
           if(direita >=13)  // se caso a distância da parede a direita estiver maior ou igual a 13 cm, o robô aumenta
                             // sua velocidade do motor esquerdo para se aproximar da parede direita;
             {
               analogWrite(vel_motor_esq, 255);
               analogWrite(vel_motor_dir, 60);
           
               analogWrite(e1, 255);
               analogWrite(e2, 0);
               analogWrite(d1, 0);
               analogWrite(d2, 255);                               
             }
             
                 
           if(direita <=7)   // se caso a distância da parede a direita estiver menor ou igual a 8 cm, o robô aumenta
                             // sua velocidade do motor direito para se distanciar da parede direita;
             {
               analogWrite(vel_motor_esq, 60);
               analogWrite(vel_motor_dir, 255);
           
               analogWrite(e1, 255);
               analogWrite(e2, 0);
               analogWrite(d1, 0);
               analogWrite(d2, 255);                   
             }
         }
         
              
       if(esquerda <=20 && direita>20 && frente <=8) dir(); //se caso a distância a frente for menor ou igual a 8 cm,
                                                            //a distancia a direita for maior que 20 cm e a distância
                                                            //a esquerda for menor ou igual a 20 cm ele chama a função dir();   
            
       if(esquerda >20 && direita>20 && frente <=8) dir(); //se caso a distância a frente for menor ou igual a 8 cm,
                                                            //a distancia a direita for maior que 20 cm e a distância
                                                            //a esquerda for maior que 20 cm ele chama a função dir(); 
       
       if(direita <=20 && esquerda>20 && frente <=8) esq(); //se caso a distância a frente for menor ou igual a 8 cm,
                                                            //a distancia a direita for menor ou igual a 20 cm e a distância
                                                            //a esquerda for maior a 20 cm ele chama a função esq(); 
       
       if(direita<=20 && esquerda<=20 && frente<=8) voltar(); //se caso a distância a frente for menor ou igual a 8 cm,
                                                            //a distancia a direita for menor ou igual a 20 cm e a distância
                                                            //a esquerda for menor ou igual a 20 cm ele chama a função voltar();                              
    
    }
       
    void esq() // função para fazer com que o robô gire 90º a esquerda se caso não tiver saída a frente e a direita;
      {
       
        analogWrite(vel_motor_esq, 120);
        analogWrite(vel_motor_dir, 120);
           
        analogWrite(e1, 0);
        analogWrite(e2, 255);
        analogWrite(d1, 0);
        analogWrite(d2, 255);
        delay(700);      
        
      }
    
    void dir() // função para fazer com que o robô gire 90º a direita se caso não tiver saída a frente ou a esquerda;
      {
        
      
        analogWrite(vel_motor_esq, 120);
        analogWrite(vel_motor_dir, 120);
        
        analogWrite(e1, 255);
        analogWrite(e2, 0);
        analogWrite(d1, 255);
        analogWrite(d2, 0);             
        delay(800);
               
      }
    
    void voltar() // função para fazer com que o robô gire 180º se caso não tiver saída a frente, a direita e a esquerda;
      {
       
        analogWrite(vel_motor_esq, 120);
        analogWrite(vel_motor_dir, 120);
           
        analogWrite(e1, 255);
        analogWrite(e2, 0);
        analogWrite(d1, 255);
        analogWrite(d2, 0);
        delay(1200); 
         
      }   
  
    
    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
