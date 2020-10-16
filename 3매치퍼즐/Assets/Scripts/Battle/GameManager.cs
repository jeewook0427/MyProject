using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    bool monsterAttack = false;
    bool PlayerAttack = false;
    bool isPlaying;
    [HideInInspector]
    public static bool playerTurn = true;
    [HideInInspector]
    public bool monsterTurn = false;

    [HideInInspector]
    public bool isAttackFinish = false;

    [HideInInspector]
    public static int playerDamage;

    [SerializeField]
    GameObject hitEffect;

    [SerializeField]
    GameObject bighitEffect;

    [SerializeField]
    GameObject dragon;

    [HideInInspector]
    GameObject player;

    [SerializeField]
    GameObject turnText;

    [SerializeField]
    GameObject damageText;

    [SerializeField]
    GameObject ClearUI;

    [SerializeField]
    GameObject LoseUI;

    Animator dragonAni;
    Animator playerAni;

    public void Start()
    {
        isPlaying = true;
        playerTurn = true;
        monsterTurn = false;
        StartCoroutine(ChangeTurn());
        damageText.GetComponent<TextMesh>().color = Color.red;
        damageText.GetComponent<TextMesh>().fontSize = 50;
        dragonAni = dragon.GetComponent<Animator>();

        Match3.ComboCount = 0;
        Match3.puzzleCount = 0;
      
    }
    public void Update()
    {
        if (player == null)
        {
            player = GameObject.FindGameObjectWithTag("Player");
            playerAni = player.GetComponent<Animator>();
        }
        if (Match3.ComboCount > 0 && !PlayerAttack && !isAttackFinish)
        {
            PlayerAttack = true;
            StartCoroutine(PlayerAttackFunc());
        }

        if (Match3.ComboCount == 0)
        {
            PlayerAttack = false;
        }

        if (dragon.GetComponent<Dragon>().HP <= 0)
        {
            ClearUI.SetActive(true);
        }
    }

    IEnumerator HitEffect()
    {
        if (playerTurn)
        {
            //GameObject hitEffecttemp = Instantiate(hitEffect);
            //hitEffecttemp.transform.position = dragon.transform.position;
            //hitEffecttemp.SetActive(true);
            yield return new WaitForSeconds(0f);
            //Destroy(hitEffecttemp);
        }

        else if (monsterTurn)
        {
            //yield return new WaitForSeconds(2);
            //GameObject hitEffecttemp = Instantiate(hitEffect);
            //hitEffecttemp.transform.position = player.transform.position;
            //hitEffecttemp.SetActive(true);
            yield return new WaitForSeconds(0f);
            //Destroy(hitEffecttemp);
        }

    }

    IEnumerator BigHitEffect()
    {
        if (playerTurn)
        {
            //GameObject hitEffecttemp = Instantiate(bighitEffect);
            //hitEffecttemp.transform.position = dragon.transform.position;
            //hitEffecttemp.SetActive(true);
            yield return new WaitForSeconds(0);
            //Destroy(hitEffecttemp);
        }


    }

    IEnumerator ChangeTurn()
    {
        if (isPlaying)
        {
            if (playerTurn)
            {
                yield return new WaitForSeconds(5);
                playerTurn = false;
                monsterTurn = true;
                isAttackFinish = false;
                PlayerAttack = false;

                Match3.ComboCount = 0;
                Match3.puzzleCount = 0;
                StartCoroutine(TurnTextRender());
                StartCoroutine(ChangeTurn());
                //StartCoroutine(HitEffect());
                dragonAni.SetTrigger("isAttack");
                //StartCoroutine(DamageTextRender());
            }

            else if (monsterTurn)
            {
                yield return new WaitForSeconds(5);
                playerTurn = true;
                monsterTurn = false;
                StartCoroutine(TurnTextRender());
                StartCoroutine(ChangeTurn());
            }
        }
    }

    IEnumerator TurnTextRender()
    {
        if (isPlaying)
        {
            if (monsterTurn)
            {
                turnText.GetComponent<TextMesh>().text = "Monster Turn";
                turnText.GetComponent<TextMesh>().color = Color.red;
                turnText.GetComponent<TextMesh>().fontSize = 50;
                turnText.GetComponent<TextMesh>().transform.position += new Vector3(1f, -1f, 0);
                turnText.SetActive(true);
                yield return new WaitForSeconds(1);
                turnText.SetActive(false);
            }
            else if (playerTurn)
            {
                turnText.GetComponent<TextMesh>().text = "Player Turn";
                turnText.GetComponent<TextMesh>().color = Color.blue;
                turnText.GetComponent<TextMesh>().fontSize = 60;
                turnText.GetComponent<TextMesh>().transform.position += new Vector3(-1f, 1f, 0);
                turnText.SetActive(true);
                yield return new WaitForSeconds(1);
                turnText.SetActive(false);
            }
        }

    }

    IEnumerator PlayerAttackFunc()
    {
        playerAni.SetTrigger("isAttack");
        yield return new WaitForSeconds(.5f);
        playerDamage = Match3.ComboCount * Match3.puzzleCount * player.GetComponent<Character>().attackValue;

       
            //StartCoroutine(DamageTextRender());
            yield return null;
        //if (!isAttackFinish)
        //{

        //    playerDamage = Match3.ComboCount * Match3.puzzleCount * player.GetComponent<Character>().attackValue;
        //    if (playerDamage > 400)
        //    {
        //        StartCoroutine(BigHitEffect());
        //       // StartCoroutine(DamageTextRender());
        //    }

        //    else
        //    {
        //        StartCoroutine(HitEffect());
        //       // StartCoroutine(DamageTextRender());
        //    }

        //    isAttackFinish = true;
        //}
    }

    IEnumerator DamageTextRender()
    {
        if (monsterTurn)
        {           
            yield return new WaitForSeconds(2);
            damageText.SetActive(false);
        }

        else if (playerTurn)
        {
            yield return new WaitForSeconds(2);
            damageText.SetActive(false);
        }

    }

}