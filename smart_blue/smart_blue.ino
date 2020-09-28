//주) 노드MCU 보드에 업로드시 와이파이보드 RX, TX핀을 제거하고 업로드
char rxVal;//스마트폰->노드MCU보드 전송값 변수 선언
//int LED_USER = 14;//외부(하단) LED 변수 선언 GPIO 14번=프린팅된번호D5
int LED_USER = 16;//외부(하단) LED 변수 선언 GPIO 16번=프린팅된번호D0
//주) 노드MCU는 LOW 와 HIGH 가 일반 아두이노와 반대
int ON = 0; //HIGH
int OFF = 1; //LOW

void setup() //프로그램 초기 1회만 실행됨
{
  //시리얼 모니터 설정(아래)
  Serial.begin(9600);//불루투스보드와 통신연결-아두이노내장 시리얼모니터에서 사용.
  Serial.println();//자바의 System.out.println()과 같음
  //노드MCU 보드 핀 설정(아래)
  pinMode(LED_BUILTIN, OUTPUT);//MCU보드의 상단 led 켜기 선언
  pinMode(LED_USER, OUTPUT);//외부(하단) led 켜기 선언
  digitalWrite(LED_BUILTIN, OFF);//MCU보드의 상단 led OFF
  digitalWrite(LED_USER, OFF);//외부(하단) led OFF
}//End setup()

void loop()                 //MCU보드 전원이 꺼질때까지 무한 실행됨
{
 static boolean flag = true;// flag 가 참일 경우
 if(Serial.available())//불루투스보드와 통신연결이 되었을때 if 실행
 {
  rxVal = Serial.read();                          
  Serial.println(int(rxVal));   //Serial Monitor로 수신값 출력
  switch(rxVal)
  {
    case '1' :                  // rxVal 이 1 일 경우
       for(int i=0; i<3; i++)   // 0부터 2까지 3회 반복
         {
          digitalWrite(LED_BUILTIN, ON);// MCU보드의 상단 led ON
          delay(500);           // 0.5초 기다림
          digitalWrite(LED_BUILTIN, OFF); // MCU보드의 상단 led OFF
          delay(500);
         }
         break;                 // switch문 종료
    case '2' :                  // rxVal 이 2 일 경우
       for(int i=0; i<3; i++)   // 0부터 2 까지 3회 반복
         {
          digitalWrite(LED_BUILTIN, ON);// MCU보드의 상단 led ON
          delay(3000);          // 3초 동안 기다림
          digitalWrite(LED_BUILTIN, OFF); // MCU보드의 상단 led OFF
          delay(3000);          // 3초 동안 기다림
         }
         break;                 // switch문 종료
    case '3' :                  // rxVal 이 4 일 경우 - 토글Toogle기능(똑딱이)
        {
          switch(flag)          // flag 가 참이면 
          {
            case true:
              digitalWrite(LED_BUILTIN, ON);// MCU보드의 상단 led ON
              flag=false;           // flag 변수에 거짓값 저장
              break;                // 내부 switch문 종료
            case false:            // flag가 거짓이면
              digitalWrite(LED_BUILTIN, OFF);// MCU보드의 상단 led OFF
              flag=true;           // flag 변수에 참값 저장
              break;               // 내부 switch문 종료
         }
         break;                   // switch문 종료
       }
    case'4' :                     //rxVal 이 5 이면
        for(int i=0; i<3; i++)    // 0부터 2 까지 3회 반복
         {
          digitalWrite(LED_USER, OFF);  // 외부(하단) led OFF
          digitalWrite(LED_BUILTIN, ON);  // MCU보드의 상단 led ON
          delay(500);                   // 0.5 초 후 
          digitalWrite(LED_USER, ON);  // 외부(하단) led ON
          digitalWrite(LED_BUILTIN, OFF);   // MCU보드의 상단 led OFF
          delay(500);                  // 0.5초 후 반복 (x 3회)
         }                             // 3회 후 반목분 종료
        digitalWrite(LED_USER, OFF);   // 외부(하단) led OFF
        digitalWrite(LED_BUILTIN, OFF);// MCU보드의 상단 led OFF
        break;                         // switch문 종료
    case '8' :                         //rxVal 이 s 일 경우 모든 led 꺼짐
        digitalWrite(LED_USER, ON);   // 외부(하단)`                                                                                                                                                                                      led OFF
        digitalWrite(LED_BUILTIN, ON);// MCU보드의 상단 led OFF 
        break;                         // switch문 종료
    case '9' :                         //rxVal 이 s 일 경우 모든 led 꺼짐
        digitalWrite(LED_USER, OFF);   // 외부(하단)`                                                                                                                                                                                      led OFF
        digitalWrite(LED_BUILTIN, OFF);// MCU보드의 상단 led OFF 
        break;                         // switch문 종료
  }// End switch문
 }// End if문
}// End loop문
