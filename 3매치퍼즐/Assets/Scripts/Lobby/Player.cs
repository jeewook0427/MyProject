using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public struct CharType
{
    public CharType(GameObject _charPrefab, int _hp, int _attack)
    {
        charPrefab = _charPrefab;
        hp = _hp;
        attack = _attack;
    }

    public GameObject charPrefab { get; }
    public int hp { get; }
    public int attack { get; }
}


public struct ITEMINFO
{
   // private string[] panelInfoIcon = { "UI_Graphic_Resource_Food", "UI_Graphic_Resource_Tools", "UI_Graphic_Resource_Gems", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood" };


    public ITEMINFO(string _itemName, int _itemCount, string _itemImageName)
    {
        itemName = _itemName;
        //itemType = _itemType;
     
        itemImageName = _itemImageName;
        
        itemCount = _itemCount;
    }

    public string itemName { get; }
    public string itemImageName { get; }
    // int itemType { get; }
    public int itemCount { get; set; }

}

public class Player : MonoBehaviour
{
    //연결해야 하는 객체 = HP/공격력 바; 코인 UI 인벤토리 UI;
    public GameObject hpBar;
    public GameObject attBar;
  //  public GameObject attBar;
    public Text coinUI;
    
    public GameObject inventoryUI;

    private string[] itemNames = { "HP UP!", "Crush Block", "Shuffle!", "Sorry", "Sorry", "Sorry" };
    private string[] iconImage = { "UI_Graphic_Resource_Food", "UI_Graphic_Resource_Tools", "UI_Graphic_Resource_Gems", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood" };



    [SerializeField]// 탱커 프리팹
    GameObject tankPrefab;
    [SerializeField]//일반 프리팹
    GameObject normalPrefab;
    [SerializeField]//딜러 프리팹
    GameObject dpsPrefab;
    Vector3 prefabPos = new Vector3(-9.5f,0f,-15.5f);
    Vector3 prefabRot = new Vector3(0f, 180f, 0f);
   
    List<CharType> charType;

    //선택되면 캐릭터 정보 변수
    GameObject player;
    int hp;
    int attack;
    public int charTypeNum { get; set; }
    int currCharTypeNum;

   
    //캐릭터 선택과 상관 없이 저장되어야 하는 정보;// 초기 값 1000코인
    public int coin { get; private set; }


    // 아이템 상점과 연관;
    List<ITEMINFO> items;

    // Start is called before the first frame update
    void Start()
    {
        charType = new List<CharType>();
        items = new List<ITEMINFO>();
        for (int i = 0; i < 3; i++)
        {
            int Amount = PlayerPrefs.GetInt(itemNames[i], 0);
            if (Amount != 0)
            {
                switch (itemNames[i])
                {
                    case "HP UP!":
                        items.Add(new ITEMINFO(itemNames[i], Amount, iconImage[0]));
                        break;
                    case "Crush Block":
                        items.Add(new ITEMINFO(itemNames[i], Amount, iconImage[1]));
                        break;
                    case "Shuffle!":
                        items.Add(new ITEMINFO(itemNames[i], Amount, iconImage[2]));
                        break;
                    default:
                        break;

                }
            }
        }


        charType.Add(new CharType(Instantiate(normalPrefab, prefabPos,Quaternion.Euler(prefabRot)), 75, 75));
        charType.Add(new CharType(Instantiate(tankPrefab, prefabPos, Quaternion.Euler(prefabRot)), 100, 50));
        charType.Add(new CharType(Instantiate(dpsPrefab, prefabPos, Quaternion.Euler(prefabRot)), 50, 100));
        currCharTypeNum = 0;
        charTypeNum = 0;
        for (int i =1; i< charType.Count; i++)
        {
            charType[i].charPrefab.SetActive(false);
        }

        // 초기화 되기 전에 오류가 남-> 수정함;
        hpBar.GetComponent<HpBarScript>().SetHealth(charType[charTypeNum].hp);
        attBar.GetComponent<AttBarScript>().SetHealth(charType[charTypeNum].attack);

        if (!PlayerPrefs.HasKey("Coin")) coin = 1000;
        else coin = PlayerPrefs.GetInt("Coin");
        coinUI.text = coin.ToString();
       // inventoryUI.GetComponent<InventoryScript>().SlotReSeting();
    }

    // Update is called once per frame
    void Update()
    {
        //player = charType[charTypeNum].charPrefab;
        //hp = charType[charTypeNum].hp;
        //attack = charType[charTypeNum].attack;
       
    }

    public void ChangeChar()
    {

        charType[currCharTypeNum].charPrefab.SetActive(false);
        charType[charTypeNum].charPrefab.SetActive(true);
        hpBar.GetComponent<HpBarScript>().SetHealth(charType[charTypeNum].hp);
        attBar.GetComponent<AttBarScript>().SetHealth(charType[charTypeNum].attack);
        currCharTypeNum = charTypeNum;
    }

    public void SelectChar()
    {
        //player = charType[currCharTypeNum].charPrefab;
        //hp = charType[currCharTypeNum].hp;
        //attack = charType[currCharTypeNum].attack;
        // 캐릭터 정보 저장 /타입 0~2;(노말,탱커,딜러 순)
        PlayerPrefs.SetInt("CharType", currCharTypeNum);
        // 캐릭터 코인
        PlayerPrefs.SetInt("Coin", coin);
        // 캐릭터 아이템 
        int i = 0;
        foreach (var item in items)
        {
            //string name = "ItemType" + i;
            PlayerPrefs.SetInt(item.itemName, item.itemCount);
            i++;
        }

    }

    public void AddItem(string name, int cost, string iconName)
    {
         bool hasItem = false;
           for( int  i = 0; i< items.Count; i++)
            {
                if(items[i].itemName == name)
                {
                    hasItem = true;
                    ITEMINFO temp = items[i];
                    temp.itemCount += 1;
                    items[i] = temp;
                    break;
                }
            }

            if(!hasItem)
            {
                items.Add(new ITEMINFO (name, 1, iconName));
            }
            coin -= cost;
            coinUI.text = coin.ToString();

        inventoryUI.GetComponent<InventoryScript>().SlotReSeting();
    }
    public void SetCoin()
    {
        coin += 1000;
        coinUI.text = coin.ToString();
    }
    public List<ITEMINFO> GetItemList()
    {
        return items;
    }
}
