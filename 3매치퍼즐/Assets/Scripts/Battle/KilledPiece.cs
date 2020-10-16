using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class KilledPiece : MonoBehaviour
{
    public GameObject explosion;
    public RectTransform killedBoard;

    public bool falling;

    float speed = 16f;
    float gravity = 32f;
    Vector2 moveDir;
    RectTransform rect;
    Image img;

   // public Color[] blockColors;

    GameObject explosiontemp;
   // public ParticleSystem particleLauncher;
    


    public void Initialize(Sprite piece, Vector2 start, Color blockColors)
    {
        falling = true;
  
        moveDir = Vector2.up;
        moveDir.x = Random.Range(-1.0f, 1.0f);
        moveDir *= speed / 2;

        img = GetComponent<Image>();
        rect = GetComponent<RectTransform>();
        img.sprite = piece;
        rect.anchoredPosition = start;
        
        explosiontemp = GameObject.Instantiate(explosion, killedBoard);
        ParticleSystem.MainModule newModule = explosiontemp.GetComponent<ParticleSystem>().main;
        newModule.startColor = blockColors;

        explosiontemp.SetActive(true);
        explosiontemp.transform.position = this.transform.position + new Vector3(50,40,0);
    }

    // Update is called once per frame
    void Update()
    {
        if (!falling) return;
        moveDir.y -= Time.deltaTime * gravity;
        moveDir.x = Mathf.Lerp(moveDir.x, 0, Time.deltaTime);
        rect.anchoredPosition += moveDir * Time.deltaTime * speed;
        if (rect.position.x < -900f || rect.position.x > Screen.width + 900f
            || rect.position.y < -900f || rect.position.y > Screen.height + 900f)
        {
            falling = false;
            Destroy(explosiontemp);
        }
            
    }
}
