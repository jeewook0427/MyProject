using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BattleIventoryScript : MonoBehaviour
{
    [SerializeField]
    private GameObject prefab;

    [SerializeField]
    private GameObject ButtonMgr;

    public List<ITEMINFO> Items { get; private set; } = new List<ITEMINFO>();
    private GameObject slot;
    private List<GameObject> slots = new List<GameObject>();
    private string[] itemNames = { "HP UP!", "Crush Block", "Shuffle!", "Sorry", "Sorry", "Sorry" };
    private string[] iconImage = { "UI_Graphic_Resource_Food", "UI_Graphic_Resource_Tools", "UI_Graphic_Resource_Gems", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood" };



    // Start is called before the first frame update
    void Start()
    {
        
        // 아이템 리스트 저장
        for (int i = 0; i< 3;i++ )
        {
            int Amount = PlayerPrefs.GetInt(itemNames[i], 0);
            if (Amount != 0)
            { 
                 switch (itemNames[i])
                  {
                    case "HP UP!":
                        Items.Add(new ITEMINFO(itemNames[i], Amount, iconImage[0]));
                        break;
                    case "Crush Block":
                        Items.Add(new ITEMINFO(itemNames[i], Amount, iconImage[1]));
                        break;
                    case "Shuffle!":
                        Items.Add(new ITEMINFO(itemNames[i], Amount, iconImage[2]));
                        break;
                    default:
                        break;

                 }
            }
        }
        // 아이템 슬롯 출력
        if (slots.Count <= 0)
        {
            for (int i = 0; i < 3; i++)
            {
                
                slot = Instantiate(prefab, new Vector3(transform.position.x, ((i * (-16f))+ transform.position.y-1), transform.position.z), transform.rotation, gameObject.transform);
                int a = 1 + i;
                slot.transform.GetChild(0).gameObject.SetActive(false);
                slot.GetComponent<Button>().onClick.AddListener(ButtonMgr.GetComponent<BattleButtonScript>().ItemButtonClick); //= ButtonMgr.GetComponent<BattleButtonScript>().ItemButtonClick();
                slots.Add(slot);

                
            }
        }

        SlotReSeting();




    }

    // Update is called once per frame
    void Update()
    {
        
    }



    public void SlotReSeting()
    {
        //if (items == null)
        //    items = player.GetComponent<Player>().GetItemList();
        if (Items != null)
        {
            int i = 0;
            foreach (var item in Items)
            {
                slots[i].name = item.itemName;
                slots[i].transform.GetChild(0).gameObject.GetComponent<Image>().sprite = Resources.Load<Sprite>(item.itemImageName);
                slots[i].transform.GetChild(0).gameObject.SetActive(true);
                slots[i].transform.GetChild(0).gameObject.transform.GetChild(0).GetComponent<Text>().text = item.itemCount.ToString();
                i++;
            }
        }
    }

    public void UseItem(string name)
    {
    // 
    
        for (int i = 0; i < Items.Count; i++)
       {
           if (Items[i].itemName == name)
           {
                if (Items[i].itemCount > 0)
                {
                    ITEMINFO temp = Items[i];
                    temp.itemCount -= 1; 
                    Items[i] = temp;
                    SlotReSeting();
                }
               break;
           }
       }


          

    }

}
