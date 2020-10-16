using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class BattleButtonScript : MonoBehaviour
{
    
    [SerializeField]
    private GameObject ClearUI;
    [SerializeField]
    private GameObject LoseUI;
    [SerializeField]
    private GameObject IventoryUI;
    [SerializeField]
    private GameObject lodingUI;
    [SerializeField]
    private Slider loadingBar;
    [SerializeField]
    private Text loadinText;

    private List<ITEMINFO> items ;
    private bool hasClick;
    // Start is called before the first frame update
    void Start()
    {
        hasClick = false;
        items = new List<ITEMINFO>();
   
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void ItemButtonClick()
    {
        string name = EventSystem.current.currentSelectedGameObject.name;
        IventoryUI.GetComponent<BattleIventoryScript>().UseItem(name);

    }

    public void LoseButtonClick()
    {
       
        if (!hasClick)
        {
            items = IventoryUI.GetComponent<BattleIventoryScript>().Items;
            // 캐릭터 아이템 
            foreach (var item in items)
            {
                PlayerPrefs.SetInt(item.itemName, item.itemCount);
            }
            LoseUI.SetActive(false);
            lodingUI.SetActive(true);
            loadingBar.gameObject.SetActive(true);
            StartCoroutine(Loading());
            hasClick = true;
        }
    }

    public void ClearButtonClick()
    {
        
        if (!hasClick)
        {
            int coin = PlayerPrefs.GetInt("Coin");
            PlayerPrefs.SetInt("Coin", coin+500);
            items = IventoryUI.GetComponent<BattleIventoryScript>().Items;
            // 캐릭터 아이템 
            foreach (var item in items)
            {
                PlayerPrefs.SetInt(item.itemName, item.itemCount);
            }
            ClearUI.SetActive(false);
            lodingUI.SetActive(true);
            loadingBar.gameObject.SetActive(true);
            StartCoroutine(Loading());
            hasClick = true;
        
        }
    }


    IEnumerator Loading()
    {
        yield return null;
        AsyncOperation operation = SceneManager.LoadSceneAsync("Lobby Scene");
        operation.allowSceneActivation = false;
        while (!operation.isDone)
        {
            yield return null;
            if (loadingBar.value < 0.9f)
            {
                loadingBar.value = Mathf.MoveTowards(loadingBar.value, 0.9f, Time.deltaTime);

                if (loadingBar.value < 0.3f)
                    loadinText.text = "Looking For Sword...";
                else if (loadingBar.value >= 0.3f && loadingBar.value < 0.6f)
                    loadinText.text = "Looking For Shield...";
                else if (loadingBar.value >= 0.6f && loadingBar.value < 0.8f)
                    loadinText.text = "Looking For Friend...";
                else if (loadingBar.value >= 0.8f)
                    loadinText.text = "Good Luck For You!";

            }
            else if (operation.progress >= 0.9f)
            {
                loadingBar.value = Mathf.MoveTowards(loadingBar.value, 1f, Time.deltaTime);

                if (loadingBar.value < 0.3f)
                    loadinText.text = "Looking For Sword...";
                else if (loadingBar.value >= 0.3f && loadingBar.value < 0.6f)
                    loadinText.text = "Looking For Shield...";
                else if (loadingBar.value >= 0.6f && loadingBar.value < 0.8f)
                    loadinText.text = "Looking For Friend...";
                else if (loadingBar.value >= 0.8f)
                    loadinText.text = "Good Luck For You!";

            }

            if (loadingBar.value >= 1f)
            {
                if (operation.progress >= 0.9f)
                { operation.allowSceneActivation = true; }
            }



        }
    }
}
