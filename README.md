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
> 자세한 내용은 pdf 참고<br />
> https://github.com/ho9909/MFC_img/blob/main/MFC%20%EC%98%81%EC%83%81%EC%B2%98%EB%A6%AC.pdf
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


