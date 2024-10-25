# Potforio
## MarkDown 사용법
https://github.com/kimasill/MarkDown/blob/main/README.md?plain=1

## 목차  
### 일지 
[1주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/1Week.md)  
[2주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/2Week.md)  
[3주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/3Week.md)  
[4주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/4Week.md)  
[5주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/5Week.md)  
[6주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/6Week.md)  
[7주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/7Week.md)  
[8주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/8Week.md)  
[9주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/9Week.md)  
[10주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/10Week.md)  
[11주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/11Week.md)  
[12주차](https://github.com/hiki25/Portfolio/blob/main/ReadMeFile/12Week.md)  

## 기술 문서
### Components
#### ActionComponent
Character들이 가지고 있는 무기에 따라 행하는 행동을 제어하는 Component입니다.<br/>
가지고 있는 무기를 ActionType(Enum)으로 판단하며 Player는 이 ActionType을 통해 무기를 변경 할 수 있습니다.<br/>
행하는 행동들은 DataAsset에 저장되어 있는 AnimMontage를 실행 합니다.
<br/>
[DataAsset](#DataAsset)
#### StateComponent
Character들의 상태를 관리하는 Component입니다.<br/>
EStateType(Enum 타입)으로 Character들의 상태를 정의합니다.<br/>
함수를 통해 상태를 변경할 수 있으며, 현재 상태를 검사할 수 도 있습니다.<br/>
상태를 변경할 시 Delegate를 사용하여 상태에 맞는 행동을 하게 하였습니다.<br/>
많은 타입이 있지만 가장 대표적인 Type은 Idle 입니다. 이 Idle은 어떠한 행동도 하지 않은 상태를 의미합니다.<br/>
다양한 Type들이 존재하며 상태에 맞는 행동을 하기 전에 상태를 변경하며 이 행동을 하는 동안에는 다른 행동이 불가합니다.<br/> Ex)공격중인 상태(Action)에서 무기를 장착 또는 해제(Equip, UnEquip)를 할 수 없습니다.
#### MontageComponent  
Character들이 공동으로 행해야하는 Montage를 관리하는 Component 입니다.<br/>
Montage가 재생되려면 위에 서술한 StateComponent를 통해 재생이 됩니다.<br/>
재생될 Montage들은 구조체로 저장하여 관리합니다.<br/>
구조체는 StateType, UAnimMotage, PlayRate(float Type), StartSection(FName)을 가진다.<br/>

#### DataAsset

