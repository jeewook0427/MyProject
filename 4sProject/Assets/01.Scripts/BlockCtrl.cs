using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockCtrl : MonoBehaviour
{

    private GameObject Camera;
    private GameObject UIManager;
    private float blockSpeed;
    

    [System.NonSerialized]
    public int blockDirection = 0;
    

    private bool isCollision = false;

    void Start()
    {
        blockSpeed = (float)Random.Range(25, 35) / 10;
        Camera = GameObject.FindGameObjectWithTag("MainCamera");
        UIManager = GameObject.FindGameObjectWithTag("GameManager");
    }

    // Update is called once per frame
    void Update()
    {
        if(!GameManager.GameOver && !isCollision)
        {
            if (Mathf.Abs(transform.position.x - 4.168f) >= 0.05f)
            {
                if(blockDirection ==0)
                       transform.Translate(-blockSpeed * Time.deltaTime, 0, 0);            

                else
                    transform.Translate(blockSpeed * Time.deltaTime, 0, 0);
            }
               
            else
                transform.position =new Vector3 (4.168f, transform.position.y, transform.position.z);
            
        }
           
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (!GameManager.GameOver)
        {
            if (collision.gameObject.tag == "Player")
            {
                Vector3 normalVec = collision.contacts[0].normal;
                if (normalVec == (new Vector3(0, 0, 0) - new Vector3(0, 1, 0)))
                {
                    Debug.Log("윗면 충돌");
                    plusScoreFunc();
                    Camera.GetComponent<CameraMove>().cameraMoveUp = true;
                    isCollision = true;
                }

                else
                {
                    Debug.Log("옆면 충돌");
                    Rigidbody playerRb = collision.gameObject.GetComponent<Rigidbody>();
                    playerRb.constraints = RigidbodyConstraints.None;
                    if (blockDirection == 0)
                        playerRb.AddForce(new Vector3(-4f, 0, 0), ForceMode.Impulse);

                    else
                        playerRb.AddForce(new Vector3(4f, 0, 0), ForceMode.Impulse);


                    GameManager.GameOver = true;
                }
            }
        }
    }

    void plusScoreFunc()
    {
        if (transform.position.x == 4.168f)
        {
            UIManager.GetComponent<UIManager>().IncreaseScore(1+ UIManager.GetComponent<UIManager>().plusScore);

            UIManager.GetComponent<UIManager>().plusCount++;

            UIManager.GetComponent<UIManager>().IncreasePlusScore(UIManager.GetComponent<UIManager>().plusScore, transform.position.y);

            if (UIManager.GetComponent<UIManager>().plusCount == UIManager.GetComponent<UIManager>().plusScore)
            {
                UIManager.GetComponent<UIManager>().plusScore++;
                UIManager.GetComponent<UIManager>().plusCount = 0;
            }

            
        }

        else
        {
            UIManager.GetComponent<UIManager>().IncreaseScore(1);

            UIManager.GetComponent<UIManager>().plusScore = 1;
            UIManager.GetComponent<UIManager>().plusCount = 0;
        }

        

       
      
        
       
    }

}
