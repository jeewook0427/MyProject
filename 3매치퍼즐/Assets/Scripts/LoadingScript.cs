using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LoadingScript : MonoBehaviour
{
    public Slider loadingBar;
    public Text loadinText;
    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(Loading());
    }

    // Update is called once per frame
    void Update()
    {
        
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
