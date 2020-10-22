using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    [System.NonSerialized]
    public bool cameraMoveUp = false;

    private GameObject UIManager;
    private Vector3 temp;
    // Start is called before the first frame update
    void Start()
    {
        transform.position = new Vector3(4.126999f, 1.774f, -7.71f);
        UIManager = GameObject.FindGameObjectWithTag("GameManager");
    }

    // Update is called once per frame
    void Update()
    {
        moveUp();

        moveEnd();
    }

    public void moveUp()
    {
        if(!GameManager.GameOver)
        {
            if (!cameraMoveUp)
                temp = transform.position;

            if (cameraMoveUp)
            {
                transform.position = Vector3.Lerp(transform.position,
                        new Vector3(transform.position.x, transform.position.y + 0.5f, transform.position.z), 2f * Time.deltaTime);
                                
                if (temp.y + 0.5f <= transform.position.y)
                {
                    cameraMoveUp = false;
                }
            }

        }
       
    }

    public void moveEnd()
    {
        if(GameManager.GameOver)
        {
            transform.position = Vector3.Lerp(transform.position,
                   new Vector3(transform.position.x, temp.y, temp.z-5f), 2f * Time.deltaTime);

            
            UIManager.GetComponent<UIManager>().gameOverFunc();
            
        }

    }
}
