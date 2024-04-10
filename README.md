# Harnamana_cardon

## 폴더 전체 불러오기
* git clone https://github.com/JIHOON7712/harnamana_cardon.git

## 실행 방법
```
g++ -o audio-control audio control.cpp
gcc music_player.c
./a.out
```

## git 관리 방법

```
#Branch 관리하기
git branch process_ji
git checkout process_ji

#매일 작성한 내용 올리기
git add .
git commit -m "오늘 수정한 내용"
git push

#항상 작업하기 전에 main을 불러오고 난 후에 작업할 것
git pull origin main 
```

## 주의 사항
1. 항상 자기 브랜치에서 작업하기
2. main 주기적으로 pull 하고 작업하기
3. Main에 넣어야 할 내용이면 push 하고 나서 Github 사이트 들어와서 pull-request까지 꼭! 남기기