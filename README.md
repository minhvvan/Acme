# Acme
<img src="https://github.com/minhvvan/Acme/assets/59609086/a0316d79-ab51-4210-919b-be6cef12af10" width="1000" height="500">

본 프로젝트는 '두들 갓'이라는 게임을 모티브로 제작한 게임입니다.

4가지의 원소를 기반으로 다양한 아이템을 제작하며 생존하는 게임입니다.

- Engine: UE5.3
- Env: Visual Studio
- 제작기간: 2023.12 ~ 2024.03
- 인원: 1명

</br>
</br>
</br>
</br>
</br>


# Architecture



</br>
</br>
</br>
</br>
</br>


# Level
## Lobby

|기본 화면|기존 게임|
|------|---|
|![image](https://github.com/minhvvan/Acme/assets/59609086/bc3b8b99-55ea-4e5b-bd53-9df7745cd4dc)|![image](https://github.com/minhvvan/Acme/assets/59609086/20a26789-69e5-4227-9cec-132efa8ea003)|

- 기존 게임을 눌러 저장한 게임을 불러올 수 있습니다.

</br>
</br>

## Game

### Landscape
<img width="741" alt="image" src="https://github.com/minhvvan/Acme/assets/59609086/37ab653b-bd70-4593-9e7e-b4b34eddfbca">

### Start Village

![image](https://github.com/minhvvan/Acme/assets/59609086/86b788d4-fe95-4adc-8ba7-497237ab4d85)

### Capital

![image](https://github.com/minhvvan/Acme/assets/59609086/cf3d1fd9-1f68-4ee1-aa7d-71bfbb697640)

</br>
</br>
</br>
</br>
</br>



# Widget

### Guide
| | |
|------|---|
|![image](https://github.com/minhvvan/Acme/assets/59609086/f9932618-4367-4252-be6a-3f8e9c75bdc1)|![image](https://github.com/minhvvan/Acme/assets/59609086/ed394c42-7435-40e1-851a-aeac6447ec3b)|
|![image](https://github.com/minhvvan/Acme/assets/59609086/50f8ef8b-4e93-463e-827e-ef74ae93730b)|![image](https://github.com/minhvvan/Acme/assets/59609086/212aae9d-b2b8-48c2-bbe1-7a0b23589117)|

</br>

- 게임에 처음 접속했을 때, 게임에 대한 정보를 볼 수 있는 가이드 위젯입니다.
- 조작법과 시스템에 대한 설명이 있습니다.
- 하단에 체크박스를 통해 다음에 다시 볼것인지 설정할 수 있습니다.

</br>
</br>

### Inventory
![image](https://github.com/minhvvan/Acme/assets/59609086/8f3a6581-3d59-47bd-a4d4-7f66e68b8d24)

</br>

- 'Tab'키를 통해 열 수 있는 인벤토리 위젯입니다.
- 플레이어가 소지한 아이템을 카테고리별로 볼 수 있으며 장비를 장착할 수 있습니다.
- 퀵슬롯에 아이템을 등록하여 사용할 수 있습니다.

</br>
</br>


### Alchemy
|Alchemy Cauldron|Widget|
|--|--|
|![image](https://github.com/minhvvan/Acme/assets/59609086/75ecb51c-631d-45f8-b346-eeba82cb6af3)|![image](https://github.com/minhvvan/Acme/assets/59609086/50152eb0-6d10-4caa-a7e5-3f9a7b73f004)|

</br>

- 소유한 원소나 아이템을 합성할 수 있는 위젯입니다.
- 좌클릭을 통해 합성할 아이템을 등록할 수 있고, 우클릭을 통해 등록한 아이템을 해제할 수 있습니다.
- 합성버튼을 클릭하면 합성에 소모한 아이템은 사라지고 결과로 나온 아이템을 획득합니다.
- 만약, 합성이 불가능한 조합이라면 경고 위젯이 팝업됩니다.

</br>
</br>


### Cook Pot
|Cook Pot|Widget|
|--|--|
|![image](https://github.com/minhvvan/Acme/assets/59609086/6a2fc1fd-cfbc-42ba-9b32-8540d4b358cb)|![image](https://github.com/minhvvan/Acme/assets/59609086/3de81d96-356a-4022-9e34-d621c742b44a)|

</br>

- 등록된 레시피를 통해 음식을 제작할 수 있는 위젯입니다.
- 레시피를 클릭하면 재료를 볼 수 있으며, 소유 여부를 보여줍니다.
- 제작버튼을 통해 음식을 제작할 수 있습니다.

</br>
</br>

### Potion
|Potion|Widget|
|--|--|
|![image](https://github.com/minhvvan/Acme/assets/59609086/dab7a5cc-89a5-43ef-b0e8-7b6e263d1514)|![image](https://github.com/minhvvan/Acme/assets/59609086/ee7fc160-8c3a-49f2-a58a-69f16dba0525)|

</br>

- 등록된 레시피를 통해 포션을 제작할 수 있는 위젯입니다.
- 레시피를 클릭하면 재료를 볼 수 있으며, 소유 여부를 보여줍니다.
- 제작버튼을 통해 포션을 제작할 수 있습니다.

</br>
</br>


### Workbench
|Workbench|Widget|
|--|--|
|![image](https://github.com/minhvvan/Acme/assets/59609086/1dab7cee-7629-4aa4-994e-4effa54152b2)|![image](https://github.com/minhvvan/Acme/assets/59609086/0987d386-e937-4799-b806-c59c210ee76a)|

</br>

- 등록된 레시피를 통해 장비나 도구를 제작할 수 있는 위젯입니다.
- 레시피를 클릭하면 재료를 볼 수 있으며, 소유 여부를 보여줍니다.
- 제작버튼을 통해 장비와 도구를 제작할 수 있습니다.

</br>
</br>



# Item

## Spawned Item

### Element
|Fire|Water|
|-|-|
| | |
|Earth|Air|
| | |


</br>
</br>

### Env
|Fruit|Herb|
|--|--|
|![image](https://github.com/minhvvan/Acme/assets/59609086/2678ed24-2ea5-4397-8243-909182d75a5b)|![image](https://github.com/minhvvan/Acme/assets/59609086/2a7b71fe-9b49-46b3-8104-d35868b560c4)|
|특정 지역에 생성되는 과일입니다. </br> 음식의 재료로 사용됩니다.|특정 지역에 생성되는 약초입니다. </br> 포션의 재료로 사용됩니다.|


</br>
</br>
</br>
</br>
</br>

## Anim

### Retargeting
![Retargeting](https://github.com/minhvvan/Acme/assets/59609086/e3551c6f-b197-49c2-9666-33af410da72d)

### Move
![Move](https://github.com/minhvvan/Acme/assets/59609086/d9a63d06-8e48-4176-8f39-3dc850788c60)

### ~~Dash~~(deprecated)
![Dash](https://github.com/minhvvan/Acme/assets/59609086/99ce44cf-75e2-4c33-bab2-1bc2f2d7ef58)

### Equip
![Attach](https://github.com/minhvvan/Acme/assets/59609086/fce66afb-0f72-4010-8db9-f6d72db21a31)

### Attack
![Attack](https://github.com/minhvvan/Acme/assets/59609086/c773eb0d-6210-43ad-9ee1-95654d51b46c)

### Attacked

### DodgeRoll
![DodgeRoll](https://github.com/minhvvan/Acme/assets/59609086/e5eeb380-634a-40d8-87db-9a3489774f01)

### Swim

### Death

</br>
</br>
</br>
</br>
</br>

## System
(hp, 배고픔, 스테미나)


</br>
</br>
</br>
</br>
</br>

## NPC

</br>
</br>
</br>
</br>
</br>

## Monster
### Goblin

</br>
</br>

### Dragon





## 23.12.22
전반적인 Animation 작업을 마쳤다.
가장 힘들었던 부분은 Asset이 부족해서 원하는 느낌을 구현할 수 없는 것이었다.
예를 들면, Skill Icon을 구할 수 없어서 Skill을 콤보 액션으로 대체하여 작업하였고, 기본적은 컨셉을 조금 바꾸게 되었다.
또한, 퀄리티좋은 Animation이나 FX들을 구하기도 힘들어 타협해야 했다.
Retargeting작업은 전에 해봤었는데 기억이 나지 않아 다시 공부하며 작업했다.
두 번째 하는 작업이어서 보이는게 더 많았던 것 같다.
이번 작업으로 이해도가 많이 증가한 것 같다.
특히, RootMotion에 대한 이해가 늘어 원하는 느낌의 Motion을 적용할 수 있게 되었다.

Anim Montage를 통한 Combo Attack을 만드는 작업을 마쳤다.
Attack Input에 입력 횟수에 따라 다른 Motion이 연속적으로 진행되게 작업을 하고 싶었는데
JumpSection을 이용하여 작업을 하게되면 선행 Motion이 끝나기 전에 다음 동작을 실행하여 너무 빠른 느낌이었다.
이 문제를 Attack Input을 Queue에 입력을 모두 넣어 놓고 MontageEnd Delegate를 이용하여 Queue를 Flush하게끔 만들어서 Montage가 끝나자마자 다음 동작이 실행되게 작업했다.
하지만, 이렇게 작업하면 Animation이 끝나며 다음 동작이 실행될때 부드럽게 연결되지 않아 Motion이 튀는 느낌이 있었다.
따라서, MontageEnd Delegate가 아닌 MontageBlendingOut에 걸어 부드럽게 다음 동작으로 진행하게 구현하였다.

무기에 대해 작업하던 중, 무기가 캐릭터에서 떨어지는 일이 없게 설계하여 Component로 구현하고 Mesh만 Socket에 Attach하면 될것이라 판단했다.
하지만, Component에 SubComponent로 Mesh를 넣는 순간, Mesh가 (0,0,0)에 고정되어 버리게 되었다.
따라서, 무기를 Actor로 변경하였고 BeginPlay에서 정보에 따라 Spawn하여 Attach하게 변경하였다.
또한, 무기를 장착하고 해제하는 Motion을 이용하여 자연스럽게 등과 손에 Attach하게 구현하기 위해 Montage에서 Notify를 이용하여 Attach Socket을 변경하게끔 구현하였더니 자연스럽게 작업할 수 있었다.

Animation 작업과정에서 어려웠던 부분은 Slot을 사용하는 개념과 AimOffset의 적용부분이었는데 운좋게도 좋은 자료를 찾을 수 있어 참고하여 작업했다.
어느 정도 이해는 하였지만 완벽하게 이해한 것은 아니기 때문에 이 부분에 대해 추가적인 학습이 필요하다고 생각한다.

그리고 LandScape를 제작하는 과정에서 이해도가 부족하여 한번 했던 작업이 이상하게 변경되어 계속 같은 작업을 하기도 했다.
이 과정에서 LandScape가 동작하는 방식인 Layer에 대해 이해할 수 있었고 이 과정에 VFX제작 과정에서 패스들을 빼는 부분과 닮았다고 생각했다.
VFX에서 후반 보정 작업을 위해 중요한 부분에 대해 패스를 따로 Rendering하여 결과물을 보정한 후 다시 합치는 과정을 거치는데 이 부분과 유사하다고 생각했다.

앞으로는 Attack Montage에 Notify를 이용하여 Attack을 Check하는 부분을 구현해야 하며 속성에 따라 무기의 Mesh를 변경하는 부분에서 Niagara를 이용하여 FX를 적용해보고 싶다.
이 부분은 Houdini에서 작업했던 부분과 어느정도 비슷한것 같아 구현할 수 있을것 같다.
그 다음으로는 AI를 제외한 Monster를 작업하여 Attack이 올바르게 이루어지는지 확인해야 할 것 같다.


## 23.12.15
Inventory와 Equipment 등 필수 컴포넌트 작업을 마쳤다.
기존의 설계와 달라진 점이 많다.

원소를 이용한 스킬이나 효과등을 다르게 적용하는 전투 방식으로 설계하려 했으나 다양한 이유로 설계를 변경하기로 하였다.
우선, 가장 큰 이유는 게임의 재미적인 문제이다.
다양한 효과와 스킬을 보는 시각적 재미는 있을 수 있지만, 내가 이번에 만들고 싶은것은 플래시 게임 '두들갓'을 모티브로 하는 RPG게임이다.
즉, 제작과 연구에 재미가 가장 우선시 되어야 한다고 판단했다.
따라서, 제작을 통해 다양한 도구를 만들어 전투를 진행하고 전투의 보상으로 획득할 수 있는 아이템들을 다시 제작에 이용하는 구조로 설계를 변경하기로 했다.
이로인해 기존에 작업했던 무기나 원소 시스템의 변경이 필요했다.

 - 원소: 전투에 사용 -> 오직 제작에만 사용가능
 - 무기: 원소에 의해 변경되던 효과 -> 다양한 레시피를 통해 제작 가능한 아이템

그리고 아이템 획득 과정에서 어색한 부분이 있어 변경이 필요했다.

### 개선이 필요했던 부분
|부분|변경 전|변경 후|변경 이유|
|------|---|---|------|
|아이템 획득|애니메이션 종료 후 획득 가능 여부 체크|애니메이션을 제거하고 사용자 입력에 의해 가능 여부 체크|빠르게 움직이는 아이템을 획득할 수 없음, 아이템 획득 시 답답함이 있음|
|아이템 획득 판단|오버랩이 발생하면 아이템과 캐릭터끼리 서로를 기억하고 획득 로직을 처리|사용자 입력에 의해 캐릭터에서 가장 가까운 아이템을 체크한 뒤 획득 가능하면 획득|서로 기억하니 순환문제가 있을 수 있고 한쪽이라도 해제되면 동작하지 않는 경우가 있음, 여러 개의 아이템이 오버랩하면 오버랩이 끝나지 않은 아이템을 다시 감지하지 못함|

