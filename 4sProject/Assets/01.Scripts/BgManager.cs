using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BgManager : MonoBehaviour
{
    [Header("BackGround")]
    public GameObject bg;

    private int bgCount =1;

    private void Start()
    {
        GameObject.Instantiate(bg, new Vector3(4.197684f, 9.5f, 8.81f), Quaternion.identity);
    }

    public void MakeBg()
    {
        GameObject.Instantiate(bg, new Vector3(4.197684f, 9.5f+bgCount*30, 8.81f), Quaternion.identity);
        bgCount++;
    }
}
