using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InventoryScript : MonoBehaviour
{
    public GameObject prefab;
    public GameObject player;
    public List<ITEMINFO> Items { get; private set; } 

   
    private GameObject slot;
    List<GameObject> slots = new List<GameObject>();
    private string[] panelInfoIcon = { "UI_Graphic_Resource_Food", "UI_Graphic_Resource_Tools", "UI_Graphic_Resource_Gems", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood" };


    // Start is called before the first frame update
    void Start()
    {
        //  slots = new 
        Items = player.GetComponent<Player>().GetItemList();
        //if (slots.Count <= 0)
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                     slot = Instantiate(prefab, new Vector2((j * 154.5f) + 664.7f, (i * (-152.2f)) + 514.5f), transform.rotation, gameObject.transform);
                    int a = 1 + i + j;
                    slot.transform.GetChild(0).gameObject.SetActive(false);
                    slot.name = "slot" + a;
                    slots.Add(slot);

                }
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
        if (Items == null)
            Items = player.GetComponent<Player>().GetItemList();
        if (Items != null)
        {
            int i = 0;
            foreach (var item in Items)
            {
                slots[i].transform.GetChild(0).gameObject.GetComponent<Image>().sprite = Resources.Load<Sprite>(item.itemImageName);
                slots[i].transform.GetChild(0).gameObject.SetActive(true);
                slots[i].transform.GetChild(0).gameObject.transform.GetChild(0).GetComponent<Text>().text = item.itemCount.ToString();
                i++;
            }
        }
    }


}
