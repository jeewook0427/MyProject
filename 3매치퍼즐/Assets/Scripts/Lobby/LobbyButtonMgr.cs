using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;


public class LobbyButtonMgr : MonoBehaviour
{

    [SerializeField]
    private GameObject shopUI;
    [SerializeField]
    private GameObject content;
    [SerializeField]
    private GameObject player;
    [SerializeField]
    private GameObject Warning;
    [SerializeField]
    private GameObject lodingUI;
    [SerializeField]
    private Slider loadingBar;
    [SerializeField]
    private Text loadinText;

    private bool isSoloClick;
    private bool isMultiClick;

    int count;
    // Start is called before the first frame update
    void Start()
    {
        count = 0;
        isSoloClick = false;
        isMultiClick = false;
        //shopUI = GameObject.FindGameObjectWithTag("SHOP");
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    //캐릭터 변경 
    public void CharLeftButtonClick()
    {
       if (shopUI.activeSelf == false)
        {

            if (count == 0)
                count = 2;
            else count--;

            player.GetComponent<Player>().charTypeNum = count;
            player.GetComponent<Player>().ChangeChar();
        }
    }
    public void CharRightButtonClick()
    {
        if (shopUI.activeSelf == false)
        {
            if (count == 2)
                count = 0;
            else count++;

            player.GetComponent<Player>().charTypeNum = count;
            player.GetComponent<Player>().ChangeChar();
        }
    }


    //샵 버튼 함수
    public void ShopButtonClick()
    {
        if (shopUI.activeSelf == false)
        {
            shopUI.SetActive(true);
            content.transform.position = new Vector3(150f, content.transform.position.y, content.transform.position.z);

        }
       // content.transform.position = new Vector3(70f, content.transform.position.y, content.transform.position.z);

    }
    // 상점 종료 버튼
    public void ShopCloseButtonClick()
    {
        if (shopUI.activeSelf == true&& Warning.activeSelf==false)
        {
            shopUI.SetActive(false);
        }
    }
    //상점 구매 버튼 
    public void ShopBuyButtonClick()
    {
        if (shopUI.activeSelf == true)
        {
            
        }
        //Debug.Log();
    }
    // 금액 부족 경고 안내창 종료 버튼 
    public void WarnningCloseButtonClick()
    {
        if (shopUI.activeSelf == true)
        {
            Warning.SetActive(false);
        }

    }
    public void CoinPlusButtonClick()
    {
        player.GetComponent<Player>().SetCoin();

    }

    // 전투 버튼
    public void SoloButtonClick()
    {
        if (shopUI.activeSelf == false&&!isSoloClick)
        {
            isSoloClick = true;
            player.GetComponent<Player>().SelectChar();
            lodingUI.SetActive(true);
            loadingBar.gameObject.SetActive(true);
            StartCoroutine(Loading());
        }
    }
    public void MultyButtonClick()
    {
        if (shopUI.activeSelf == false && !isMultiClick)
        {
            isMultiClick = true;
            lodingUI.SetActive(true);
            player.GetComponent<Player>().SelectChar();
        }
    }


    IEnumerator Loading()
    {
        yield return null;
        AsyncOperation operation = SceneManager.LoadSceneAsync(2);
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
