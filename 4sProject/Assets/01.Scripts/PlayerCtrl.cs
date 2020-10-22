using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCtrl : MonoBehaviour
{
    [Header("GameManager")]
    public GameObject gameManager;
    Rigidbody rb;

    float jumpPower=8f;
    private int bgCount = 1;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        gameManager = GameObject.FindGameObjectWithTag("GameManager");
    }

    // Update is called once per frame
    void Update()
    {
        PlayerControl();
    }

    void PlayerControl()
    {
        if (!GameManager.GameOver)
        {
            if (Input.GetKeyDown(KeyCode.Space))
            {
                rb.AddForce(Vector3.up * jumpPower, ForceMode.Impulse);
            }

            if (transform.position.y >= (bgCount * 30 - 20))
            {
                gameManager.GetComponent<BgManager>().MakeBg();
                bgCount++;

            }
        }
    }
}
