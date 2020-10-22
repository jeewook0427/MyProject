using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class UIManager : MonoBehaviour
{
    private int prScore=0;

    [System.NonSerialized]
    public int plusScore = 1;
    [System.NonSerialized]
    public int plusCount = 0;

    [Header("Score")]
    public Text prScoreText;

    [Header("BestScore")]
    public Text bestScoreText;

    [Header("GameOver")]
    public Text GameOverText;

    [Header("PlusScore")]
    public Text PlusScoreText;

    private Color color = new Color(0,0,0,255f);
   
    void Start()
    {
        prScoreText.gameObject.SetActive(true);
        prScoreText.text = prScore.ToString();
        prScoreText.gameObject.GetComponent<RectTransform>().localPosition = new Vector3(1f, 157f, 0);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void IncreaseScore(int _inScore)
    {
        prScore+= _inScore;
        prScoreText.text = prScore.ToString();
        StartCoroutine("ScoreTextEffect");
    }

    public void IncreasePlusScore(int _inScore, float blockPosY)
    {
        int plusscore;
        plusscore = _inScore;
        PlusScoreText.text = "+ " + plusscore.ToString();
        PlusScoreText.gameObject.SetActive(true);
        PlusScoreText.gameObject.GetComponent<RectTransform>().localPosition = new Vector3(147f, -131.5f + blockPosY, 0);
        StartCoroutine("PlusScoreEffect");
    }

    public void gameOverFunc()
    {
        GameOverText.gameObject.SetActive(true);
        bestScoreText.gameObject.SetActive(true);
        prScoreText.gameObject.GetComponent<RectTransform>().localPosition = new Vector3(1f, 50f, 0);
        prScoreText.fontSize = 40;
        string temp = "SCORE" + System.Environment.NewLine + prScore.ToString();
        prScoreText.text = temp;
    }

    IEnumerator ScoreTextEffect()
    {
        int fontsize = 80;
        while(fontsize > 60)
        {
            prScoreText.fontSize = fontsize;
            fontsize--;
            yield return new WaitForSeconds(0.02f);
        }
        
    }

    IEnumerator PlusScoreEffect()
    {
        //while (color.a > 0)
        //{
        //    color = new Color(255f, 255f, 255f, a);
        //    PlusScoreText.color = color;
        //    a -= 15f;
        //    yield return new WaitForSeconds(0.02f);
        //}

        //a = 255f;
        yield return new WaitForSeconds(0.5f);
        PlusScoreText.gameObject.SetActive(false);
    }
}
