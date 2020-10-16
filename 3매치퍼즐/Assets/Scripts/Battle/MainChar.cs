using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainChar : MonoBehaviour
{
    [SerializeField]
    float attackValue = 1000f;
    [SerializeField]
    float HP = 100f;


    [SerializeField]// 탱커 프리팹
    GameObject tankPrefab;
    [SerializeField]//일반 프리팹
    GameObject normalPrefab;
    [SerializeField]//딜러 프리팹
    GameObject dpsPrefab;
    //GameObject tankPrefab;
    //GameObject normalPrefab;
    //GameObject dpsPrefab;
    [SerializeField]
    GameObject playerHpBar;
    GameObject player;
    Vector3 prefabPos = new Vector3(25.85f, 4f, 29.9f);
    Vector3 prefabRot = new Vector3(0f, 55f, 0f);

    int currCharTypeNum;
    // Start is called before the first frame update
    void Start()
    {
        currCharTypeNum = PlayerPrefs.GetInt("CharType");

        //tankPrefab = Resources.Load("/Prefabs/DoubleSwordFallenKing") as GameObject;
        //normalPrefab = Resources.Load("/Prefabs/SingleTwohandSwordEliteKnight") as GameObject;
        //dpsPrefab = Resources.Load("Prefabs/DoubleSwordFallenKing") as GameObject;

        switch (currCharTypeNum)
        {
            case 0:
                player = Instantiate(normalPrefab, prefabPos, Quaternion.Euler(prefabRot));
                player.GetComponent<Character>().SetHpbar(playerHpBar);
                break;
            case 1:
                player = Instantiate(tankPrefab, prefabPos, Quaternion.Euler(prefabRot));
                player.GetComponent<Character>().SetHpbar(playerHpBar);
                break;
            case 2:
                player = Instantiate(dpsPrefab, prefabPos, Quaternion.Euler(prefabRot));
                player.GetComponent<Character>().SetHpbar(playerHpBar);
                break;
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
