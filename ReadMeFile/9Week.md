## 8주차
### 목표  
1. ~~파쿠르~~
2. ~~다단히트 처리~~
3. StealTakeDown이 아닌 콤보 후 TakeDown
4. Pistol StealTakeDown? 할 지 안 할 지 모름
5. ~~Bullet HeadShot 적용~~
6. 적 처리 시 Bullet 스폰 -> 되면 MaxBullet 소모

### 달성도
#### Parkour
Tick을 통해 넘을 수 있는 벽인지 판단
1. 벽인지 판단하기
2. 넘을 수 있는 높이인지 확인
3. 벽의 깊이 확인
4. 넘을 수 있다고 판단이 되면 몽타지 재생 및 Capsule-> NoCollision, MoveMode->Flying 변경
5. 재생 후 변경 한거 원래대로 변경하기

|단계|이미지|설명|
|___|___|___|
|1|<img src = "Image/VaultFirst.png" width = 400px>|플레이어의 위치를 기준으로 2미터 앞에 충돌체가 있는지 확인한다.|
|2|<img src = "Image/VaultSecond.png" width = 400px height = 200px>|확인한 위치의 2미터 상공을 기준으로 충돌한 물체의 높이를 확인한다|
|3|<img src = Image/VaultThird.png width = 400px height = 200px>|측정된 높이가 일정높이 이상이면 물체의 길이를 측정한다|
|4|<img src = Image/VaultFourth.png width = 400px height = 200px>|위의 조건들이 다 만족하면 Vault Montage를 실행한다, 이에 맞게 상태도 변경한다|
|5|<img src = "Image/VaultEnd.png"  width = 400px height = 200px>|Montage 시간에 맞춰 다음 함수를 실행하게 **한다**|
|6|<img src = Image/VaultPlay.png height = 350px>|실행|

### 다단히트 처리
BeginOverlap시 HitCharacterNum을 HitCharacter의 수로 초기화,HitCharacter 배열에 추가 이 수가 배열의 크기보다 작다면 실행   
![Multi Hit Overlap](Image/MultiHitOverlap.png)   
배열은 Collision이 꺼질 때 Empty   
DoAction_Katana   
![Clear Hitted Character](Image/ClearHittedCharacter.png)   
CAnimNotifyState_Collision.Cpp   
![Collision Clear](Image/Collision_Clear.png)     

### DoAction_Pistol HeadShot
Enemy의 CapsuleComponent의 ObjectType을 변경 (Pawn -> PhysicsBody)   
Mesh의 Collision PreSet을 변경(World 시리즈와 Camera를 제외한 모든 Collision 무시)   
변경 시 DoAction_Katana 시 튕겨지는 버그 발견->PlayerMesh도 Enemy와 같이 변경


### Todo
StealTakeDown이 아닌 콤보 후 TakeDown을 위해 애니메이션 찾아보기 (0911)



