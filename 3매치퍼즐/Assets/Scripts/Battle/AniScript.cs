using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class AniScript : MonoBehaviour
{
    [SerializeField]
    GameObject hitEffect;

    [SerializeField]
    GameObject bighitEffect;

    GameObject player;
    GameObject dragon;

    Animator playerAni;
    Animator dragonAni;

    GameObject damageText;

    [SerializeField]
    GameObject ClearUI;

    [SerializeField]
    GameObject LoseUI;

    //[SerializeField]
    //GameObject gameManager;

    //[HideInInspector]
    //public int playerDamage;

    public void Start()
    {
        if (SceneManager.GetActiveScene().name == "BattleScene")
        {
            damageText = GameObject.FindGameObjectWithTag("DamageText");
            damageText.GetComponent<TextMesh>().color = Color.red;
            damageText.GetComponent<TextMesh>().fontSize = 50;
        }
    }

    public void PlayerAttack1()
    {
        StopAllCoroutines();
        dragon = GameObject.FindGameObjectWithTag("Dragon");
        dragonAni = dragon.GetComponent<Animator>();

        player = GameObject.FindGameObjectWithTag("Player");
        playerAni = player.GetComponent<Animator>();

        dragonAni.SetTrigger("isDamaged");

        if (GameManager.playerDamage <400)
        {
            StartCoroutine(MonsterHitEffect());
        }
        else
        {
            StartCoroutine(MonsterBigHitEffect());
        }

        StartCoroutine(PlayerDamageTextRender());
        if (dragon.GetComponent<Dragon>().HP <= 0)
        {
            playerAni.SetBool("isWin", true);
            dragonAni.SetBool("isDie", true);
        }
    }

    public void ClawAttack()
    {
        StopAllCoroutines();
        player = GameObject.FindGameObjectWithTag("Player");
        playerAni = player.GetComponent<Animator>();
        playerAni.SetTrigger("isDamaged");
    
        StartCoroutine(PlayerHitEffect());
        StartCoroutine(MonsterDamageTextRender());
    }

    IEnumerator PlayerHitEffect()
    {
        GameObject hitEffecttemp = Instantiate(hitEffect);
        hitEffecttemp.transform.position = player.transform.position;
        hitEffecttemp.SetActive(true);
        yield return new WaitForSeconds(1);
        Destroy(hitEffecttemp);
    }

    IEnumerator MonsterHitEffect()
    {
        GameObject hitEffecttemp = Instantiate(hitEffect);
        hitEffecttemp.transform.position = dragon.transform.position;
        hitEffecttemp.SetActive(true);
        yield return new WaitForSeconds(1);
        Destroy(hitEffecttemp);
    }

    IEnumerator MonsterBigHitEffect()
    {
        GameObject hitEffecttemp = Instantiate(bighitEffect);
        hitEffecttemp.transform.position = dragon.transform.position;
        hitEffecttemp.SetActive(true);
        yield return new WaitForSeconds(1);
        Destroy(hitEffecttemp);
    }

    IEnumerator MonsterDamageTextRender()
    {
        damageText.SetActive(true);
        damageText.GetComponent<TextMesh>().text = "-" + 500;
        player.GetComponent<Character>().MinusHp(10);
        damageText.GetComponent<TextMesh>().transform.position = player.transform.position + new Vector3(-9.63f, -1.94f, -6.76f);
        damageText.GetComponent<TextMesh>().transform.localScale = new Vector3(-1, 1, 1);

        yield return new WaitForSeconds(2);
        damageText.SetActive(false);
    }

    IEnumerator PlayerDamageTextRender()
    {
        damageText.SetActive(true);
        damageText.GetComponent<TextMesh>().text = "-" + GameManager.playerDamage;
        dragon.GetComponent<Dragon>().MinusHp(GameManager.playerDamage);
        // dragon.GetComponent<MonsterHpBarScript>().SetHealth(dragon.GetComponent<Dragon>().HP);
        damageText.GetComponent<TextMesh>().transform.position = dragon.transform.position + new Vector3(0f, 4.16f, -1.63f);
        damageText.GetComponent<TextMesh>().transform.localScale = new Vector3(1, 1, 1);

        yield return new WaitForSeconds(2);
        damageText.SetActive(false);
        

    }



}