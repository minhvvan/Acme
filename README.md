# Acme

## Level

<img width="741" alt="image" src="https://github.com/minhvvan/Acme/assets/59609086/37ab653b-bd70-4593-9e7e-b4b34eddfbca">

### Start Village

![image](https://github.com/minhvvan/Acme/assets/59609086/86b788d4-fe95-4adc-8ba7-497237ab4d85)

### Capital

![image](https://github.com/minhvvan/Acme/assets/59609086/cf3d1fd9-1f68-4ee1-aa7d-71bfbb697640)


## Anim

### Retargeting
![Retargeting](https://github.com/minhvvan/Acme/assets/59609086/e3551c6f-b197-49c2-9666-33af410da72d)

### Move
![Move](https://github.com/minhvvan/Acme/assets/59609086/d9a63d06-8e48-4176-8f39-3dc850788c60)

### Dash
![Dash](https://github.com/minhvvan/Acme/assets/59609086/99ce44cf-75e2-4c33-bab2-1bc2f2d7ef58)


### Equip
![Attach](https://github.com/minhvvan/Acme/assets/59609086/fce66afb-0f72-4010-8db9-f6d72db21a31)

### Attack
![Attack](https://github.com/minhvvan/Acme/assets/59609086/c773eb0d-6210-43ad-9ee1-95654d51b46c)


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
