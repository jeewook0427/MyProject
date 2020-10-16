using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum DRAGON_STATE
{
    IDLE,
    ATTACK,
    DIE,
    DAMAGED,
    APPEAR,
    END
}

public class Dragon : MonoBehaviour
{

    [SerializeField]
    DRAGON_STATE state = DRAGON_STATE.IDLE;

    //[SerializeField]
    //float attackValue = 10f;

    [SerializeField]
    private GameObject HpBar;

    public float attackValue { get; private set; }
    public float HP { get; private set; } 


    Animator anim;
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        ChangeState(DRAGON_STATE.IDLE);
        HP = 10000f;
        attackValue = 10f;
        HpBar.GetComponent<MonsterHpBarScript>().SetHealth((float)HP);
    }

    // Update is called once per frame
    void Update()
    {
        switch (state)
        {
            case DRAGON_STATE.IDLE:
                UpdateIdle();
                break;
            case DRAGON_STATE.ATTACK:
                UpdateAttack();
                break;
            case DRAGON_STATE.DIE:
                UpdateDie();
                break;
            case DRAGON_STATE.DAMAGED:
                UpdateDamaged();
                break;
            case DRAGON_STATE.APPEAR:
                UpdateAppear();
                break;
        }
    }

    public void MinusHp(int hp)
    {
        HP -= hp;
        HpBar.GetComponent<MonsterHpBarScript>().SetHealth((float)HP);
    }


    //각 상태별로 매 프레임 실행되어야 하는 구문
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
    #endregion

    #region Coroutine

    void ChangeState(DRAGON_STATE nextState)
    {
        state = nextState;
        anim.SetBool("isAttack", false);
        anim.SetBool("isIdle", false);
        //anim.SetBool("isDamaged", false);
        anim.SetBool("isAppear", false);
        anim.SetBool("isDie", false);

        StopAllCoroutines();
        switch (state)
        {
            case DRAGON_STATE.IDLE:
                StartCoroutine(CoroutineIdle());
                break;
            case DRAGON_STATE.ATTACK:
                StartCoroutine(CoroutineAttack());
                break;
            case DRAGON_STATE.DIE:
                StartCoroutine(CoroutineDie());
                break;
            //case DRAGON_STATE.DAMAGED:
                //StartCoroutine(CoroutineDamage());
                //break;
            case DRAGON_STATE.APPEAR:
                StartCoroutine(CoroutineAppear());
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

        }

        yield break;
    }

    IEnumerator CoroutineDie()
    {
        anim.SetBool("isDie", true);

        while (true)
        {
            yield return new WaitForSeconds(2f);

        }
        yield break;
    }
    IEnumerator CoroutineAppear()
    {
        anim.SetBool("isAppear", true);

        while (true)
        {
            yield return new WaitForSeconds(2f);

        }
        yield break;
    }
    //IEnumerator CoroutineDamage()
    //{
    //    anim.SetBool("isDamaged", true);
    //    while (true)
    //    {
    //        yield return new WaitForSeconds(15f);

    //        yield break;
    //    }

    //}
    #endregion


}



