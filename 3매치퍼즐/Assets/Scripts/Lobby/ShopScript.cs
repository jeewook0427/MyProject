using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ShopScript : MonoBehaviour
{
    [SerializeField]
    private GameObject prefab;
    private GameObject panel;
    [SerializeField]
    private GameObject Warning;
    [SerializeField]
    private GameObject player;
    [SerializeField]
    private GameObject shopUI;
    private struct ItemList
    {
        public ItemList(GameObject _panel, string _textAmount, string _textProduct, string _textCost, int _cost)
        {
            panel = _panel;
            textAmount = _textAmount;
            textProduct = _textProduct;
            textCost = _textCost;
            cost = _cost;

        }
        GameObject panel;
        string textAmount  { get; }
        string textProduct { get; }
        string textCost    { get; }
        int    cost      { get; }

}  
    List<GameObject> itemList;



    private string[] textAmounts = { "HP UP!", "Crush Block", "Shuffle!", "Sorry", "Sorry", "Sorry" };
    private string[] textProducts = { "HP 20% UP!", "Crushing 1block!", "Shuffle Blocks!", "Wait for Update", "Wait for Update", "Wait for Update" };
    private string[] textCosts = { "200", "300", "500", "---", "---", "---" };
    private int[] Costs = { 200,300,500,0,0,0};

    private string[] panelInfoIcon = { "UI_Graphic_Resource_Food", "UI_Graphic_Resource_Tools", "UI_Graphic_Resource_Gems", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood", "UI_Graphic_Resource_Wood" };
    

    // Start is called before the first frame update

    void Start()
    {
        //shopUI = GameObject.FindGameObjectWithTag("SHOP");
        //shopUI.SetActive(true);
        itemList = new List<GameObject>();
        for (int i = 0; i < textAmounts.Length; i++)
        {
            panel = Instantiate(prefab, new Vector2(i * 400, 11.3f), transform.rotation, gameObject.transform);
            // panel.
            panel.name = textAmounts[i];
            panel.GetComponent<PanelScript>().TextAmount.text = textAmounts[i];
            panel.GetComponent<PanelScript>().TextProduct.text = textProducts[i];
            panel.GetComponent<PanelScript>().TextCost.text = textCosts[i];
            panel.GetComponent<PanelScript>().ImgItem.sprite = Resources.Load<Sprite>(panelInfoIcon[i]);
            panel.GetComponent<PanelScript>().ShopUI = gameObject;
            itemList.Add(panel);

        }

        

    }

    // Update is called once per frame
    void Update()
    {
        //if (shopUI.activeSelf == false)
        //    Debug.Log("꺼짐");
          //  transform.position = new Vector3(-49.99f, transform.position.y, transform.position.z);
    }


    public void BuyItem(string name)
    { 
        switch(name)
        {
            case "HP UP!":
                if(player.GetComponent<Player>().coin - Costs[0]>=0)
                {
                    player.GetComponent<Player>().AddItem("HP UP!", Costs[0],"UI_Graphic_Resource_Food");

                }
                else
                {
                    Warning.SetActive(true);
                }

             break;
            case "Crush Block":
                if (player.GetComponent<Player>().coin - Costs[1] >= 0)
                {
                    player.GetComponent<Player>().AddItem("Crush Block", Costs[1],"UI_Graphic_Resource_Tools");
                }
                else
                {
                    Warning.SetActive(true);
                }
                break;
            case "Shuffle!":
                if (player.GetComponent<Player>().coin - Costs[2] >= 0)
                {
                    player.GetComponent<Player>().AddItem("Shuffle!", Costs[2], "UI_Graphic_Resource_Gems");
                }
                else
                {
                    Warning.SetActive(true);
                }
                break;
            default:
                break;

        }

    }






}
