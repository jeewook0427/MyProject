using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public enum PLAYER_STATE
{
    IDLE,
    ATTACK,
    DIE,
    DAMAGED,
    APPEAR,
    WIN,
    END
}

public class Character : MonoBehaviour
{
    [SerializeField]
    PLAYER_STATE state = PLAYER_STATE.IDLE;
    GameObject playerHpBar;
    public int attackValue { get; private set; }
    public int HP { get; private set; }
    string name;
    bool isSetting=false;
   // string[] names = { }

    Animator anim;
    // Start is called before the first frame update
    void Start()
    {
        isSetting = true;
        anim = GetComponent<Animator>();
        if (SceneManager.GetActiveScene().name == "BattleScene")
        {
            anim.SetBool("isAppear", true);
        }
        //anim.SetBool("isAppear", true);
        ChangeState(PLAYER_STATE.IDLE);

        name = gameObject.name;
        switch (name)
        {
            case "SwordShieldRedKnight(Clone)":
                attackValue = 50;
                HP = 100;
                break;
            case "SingleTwohandSwordEliteKnight(Clone)":
                attackValue = 75;
                HP = 75;
                break;
            case "DoubleSwordFallenKing(Clone)":
                attackValue = 100;
                HP = 50;
                break;
        }

    }

    // Update is called once per frame
    void Update()
    {
        switch (state)
        {
            case PLAYER_STATE.IDLE:
                UpdateIdle();
                break;
            case PLAYER_STATE.ATTACK:
                UpdateAttack();
                break;
            case PLAYER_STATE.DIE:
                UpdateDie();
                break;
            case PLAYER_STATE.DAMAGED:
                UpdateDamaged();
                break;
            case PLAYER_STATE.APPEAR:
                UpdateAppear();
                break;
            case PLAYER_STATE.WIN:
                UpdateWin();
                break;
        }
    }

    public void MinusHp(int hp)
    {
       
        HP -= hp;
        if (HP <= 0) HP = 0;
        playerHpBar.GetComponent<HpBarScript>().SetHealth((float)HP);
    }
    public void SetHpbar(GameObject _playerHpBar)
    {
        if(!isSetting)
        {
            isSetting = true;
             name = gameObject.name;
            switch (name)
            {
                case "SwordShieldRedKnight(Clone)":
                    attackValue = 50;
                    HP = 100;
                    break;
                case "SingleTwohandSwordEliteKnight(Clone)":
                    attackValue = 75;
                    HP = 75;
                    break;
                case "DoubleSwordFallenKing(Clone)":
                    attackValue = 100;
                    HP = 50;
                    break;
            }


        }

        playerHpBar = _playerHpBar;
        playerHpBar.GetComponent<HpBarScript>().SetHealth((float)HP);
    }
   

    #region Update    
    void UpdateIdle()
    {

    }

    void UpdateAttack()
    {

    }

    void UpdateDie()
    {

    }

    void UpdateDamaged()
    {

    }

    void UpdateAppear()
    {

    }
    void UpdateWin()
    {

    }
    #endregion


    #region Coroutine

    void ChangeState(PLAYER_STATE nextState)
    {
        state = nextState;
        anim.SetBool("isAttack", false);
        anim.SetBool("isIdle", false);
        anim.SetBool("isDamaged", false);
        anim.SetBool("isDie", false);

        StopAllCoroutines();
        switch (state)
        {
            case PLAYER_STATE.IDLE:
                StartCoroutine(CoroutineIdle());
                break;
            case PLAYER_STATE.ATTACK:
                StartCoroutine(CoroutineAttack());
                break;
            case PLAYER_STATE.DIE:
                StartCoroutine(CoroutineDie());
                break;
            case PLAYER_STATE.DAMAGED:
                StartCoroutine(CoroutineDamage());
                break;
            case PLAYER_STATE.APPEAR:
                StartCoroutine(CoroutineAppear());
                break;
            case PLAYER_STATE.WIN:
                StartCoroutine(CoroutineWin());
                break;
        }
    }

    IEnumerator CoroutineIdle()
    {
        anim.SetBool("isIdle", true);

        while (true)
        {
            yield return new WaitForSeconds(3f);
            yield break;
        }
    }
    IEnumerator CoroutineAttack()
    {
        anim.SetBool("isAttack", true);

        while (true)
        {
            yield return new WaitForSeconds(3f);
            //ChangeState(DRAGON_STATE.IDLE);
            yield break;
        }


    }

    IEnumerator CoroutineDie()
    {
        anim.SetBool("isDie", true);

        while (true)
        {
            yield return new WaitForSeconds(2f);
            yield break;
        }

    }
    IEnumerator CoroutineAppear()
    {
        anim.SetBool("isAppear", true);

        while (true)
        {
            yield return new WaitForSeconds(2f);
            yield break;
        }

    }
    IEnumerator CoroutineDamage()
    {
        anim.SetBool("isDamaged", true);
        while (true)
        {
            yield return new WaitForSeconds(3f);

            yield break;
        }

    }

    IEnumerator CoroutineWin()
    {
        anim.SetBool("isWin", true);
        while (true)
        {
            yield return new WaitForSeconds(3f);

            yield break;
        }

    }
    #endregion
}


