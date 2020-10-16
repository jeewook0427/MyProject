using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PanelScript : MonoBehaviour
{
    [SerializeField]
    Text textAmount;
    [SerializeField]
    Text textProduct;
    [SerializeField]
    Text textCost;
    [SerializeField]
    Image imgItem;
    [SerializeField]
    public GameObject ShopUI;

    // Start is called before the first frame update
    void Start()
    {
       // textAmount.text=
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public Text TextAmount
    {
        get { return textAmount; }
        set { textAmount = value; }
    }

    public Text TextProduct
    {
        get { return textProduct; }
        set { textProduct = value; }
    }
    public Text TextCost
    {
        get { return textCost; }
        set { textCost = value; }
    }
    public Image ImgItem
    {
        get { return imgItem; }
        set { imgItem = value; }
    }

    public void ShopBuyButtonClick()
    {
        // Debug.Log(this.gameObject.name);
        //Debug.Log(textCost.text);
        ShopUI.GetComponent<ShopScript>().BuyItem(this.gameObject.name);

    }

}
