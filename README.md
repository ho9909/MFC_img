# MFC 영상처리
> C++ MFC를 이용하여 이미지를 각종 기능들을 이용해서 데이터 추출 및 이미지 변형 기능을 구현
>
<br />

# 프로젝트 정보
> 1.제작 기간
>> 2023.04.20 - 2023.06.15
>
> 2.참여인원
>> 1인 개발
>

<br />

# 사용된 기술
>> C++

<br />

# 구현 기능
> 자세한 내용은 pdf 참고
> 1. 이미지 필터 기능( binary, sobel, gray scale) 
> 2. 이미지 열기 및 저장(PNG, JPG, RAW, BIT)
> 3. 현금판별기(지폐 한정)
>> <details><summary>자세한 내용</summary>
>> <p>
>> 현금 판별기
>> <br />
>> <img src="https://github.com/user-attachments/assets/d2bcc7bf-9ed0-4a85-8f4f-3c0b6316d863" width="50%">
>> <br />
>> 위의 예시 이미지(만원)에서 가장 중요하게 살펴봐야 하는 부분은 이미지 프로젝션 부분이다.
>> 프로젝션에서 현금의 특징을 추출해서 코드를 통해 판별을 진행후, 지폐의 여부를 파악한다.
>> 
>> 
>> </p>
> 4. 이미지에서 RGB 값 추출
> 5. 이미지에서 0~255사이의 값들을 히스토그램으로 표현
> 6. 이미지 밝기 조절 및 임계값 조절을 통한 이미지 변경 기능
> 7. 이미지 프로젝션
> 8. 이미지 평활화, 스트레칭 기능 구현
> 9. 컴퓨터 화면 녹화(전체, 부분) 및 캡처
>> <details><summary>화면 녹화 및 캡쳐</summary>
>> <p>
>> 화면 녹화 및 캡쳐 창
>> <br />

>> <img src="https://github.com/user-attachments/assets/d591f48b-1c18-44f6-afbc-a3b6a653db9c" width="50%">
>> <br />
>> 위의 이미지와 같이 캡쳐를 위한 창을 새로 열고, ffmpeg을 이용하여 캡쳐를 진행한다.
>> 녹화 기능의 경우에는 캡쳐와 동일하게 ffmpeg을 이용하는데 60fps로 표현하기 위해 1초에 60장을 캡쳐후 ffmpeg에서 사용되는 사진이어 붙이기를 통하여 영상으로 변경한다.
>> 
>> </p>
>> </details>


<br />


# 기타 참고했던 자료들
> # 참고 사이트
>> winapi 입문 강좌
>> 
>> http://soen.kr/lecture/win32api/win32lec.htm
>> 
>> http://mafa.tistory.com/entry/API-%EC%9C%88%EB%8F%84%EC%9A%B0-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%A8%EC%9D%98-%EA%B5%AC%EC%A1%B0
>> 
>> http://klkl0.tistory.com/87
>> 
>> http://wookss-blog.tistory.com/2
>> 
>> http://hackingboy.tistory.com/118
>> 
>> http://hackingboy.tistory.com/117
>> 
>> 메뉴
>> 
>> http://zetcode.com/gui/winapi/menus/
>> 
>> http://soen.kr/lecture/win32api/lec5/lec5-2-2.htm
>> 
>> https://www.daniweb.com/programming/software-development/threads/287455/winapi-getopenfilename-and-getsavefilename-not-working#
>> 
>> 다이얼로그
>> 
>> http://winnerz.tistory.com/entry/Basic-DialogBox%EB%A9%94%EC%9D%B8%EC%B0%BD%EC%9D%84-%EB%8B%A4%EC%9D%B4%EC%96%BC%EB%A1%9C%EA%B7%B8%EB%B0%95%EC%8A%A4%EB%A1%9C-%EB%9D%84%EC%9A%B0%EA%B8%B0
>> 
>> http://blog.naver.com/PostView.nhn?blogId=netrance&logNo=110080318599
>> 
>> VK_가상 키
>> 
>> http://soen.kr/lecture/win32api/lec4/lec4-1-3.htm
>> 
>> https://shaeod.tistory.com/388
<br />
> 기초 내용
>> api는 윈도우즈에 있는 함수집합
>> 커널은 우리가 쓰는 것이 아니고 운영채제가 쓰는거라 건들면 안됨. 예)핸들종류

>> int WINAPI WinMain		//윈도우의 메인문 WINAPI : 윈도우 프로그램이라는 의미
>> 
>> (HINSTANCE hInstance,		//앞에 h가 붙으면 핸들이라고 생각Instance는 사용할 수 있는 객체를 만들어내는 것
>> 				//hInstance: 운영체제의 커널이 응용 프로그램에 부여한 ID
>> 					     운영채제가 어떤 프로그램인지 식별 할 수 있게함
>>  HINSTANCE hPrevInstance,
>> 
>>  LPSTR lpszCmdLine,		//szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
>> 
>>  int nCmdShow)			//iCmdShow : 윈도우가 화면에 출력될 형태
>> 
>> WNDCLASS WndClass;		//WndClass 라는 구조체 정의(밑에서 .으로 접근) //윈도우 클래스의 구조체 안의  값을 채워서 레지스터에 등록을 한다.
>> 				
>> WndClass.style = CS_HREDRAW | CS_VREDRAW;	//H는 가로, S는 세로-> 창의 가로나 세로의 변화가 생길경우 다시 그린다.
>> 
>> //WndClass.lpfnWndProc = (WNDPROC)WndProc
>>> 기본적으로 윈도우는 메세지 기반 운영체제-> 이벤트(마우스,키보드 등등을 움직이는 것)가 발생했을 때 메세지로 만들어줌
>>> 만들어준 메세지를 큐(선입선출)로 넣는다. 발생 순서대로 처리되야하기 때문
>>> 메세지에 따른 사용자 정의기능을 만들어 낼 수 있어야 한다->메세지 큐에 어떤게 들어가있는지 정확히 알아야함(WndProc가 그런 기능을 함)
>>> WndProc는 밑에있는 함수임. 값을 변경하기 위해서 포인터로 쓴다.
>> -----------------------------------------------------------------------------------------------------------------
>> hwnd = CreateWindow 윈도우 창을 만드는 것
>>

<br />
