using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MakeBlock : MonoBehaviour
{
    [Header("Block Prefab")]
    public GameObject block;

    [Header("Block Material")]
    public Material[] blockMaterial;
        
    private int blockType;
    private int blockDirection;
    private float blockCount=0;
    
    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine("MakeBlockFunc");
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    IEnumerator MakeBlockFunc()
    {
        if (!GameManager.GameOver)
        {
            float waitTime = (float)Random.Range(8, 15) / 10;
            blockType = Random.Range(0, 3);
            blockDirection = Random.Range(0, 2);
            yield return new WaitForSeconds(waitTime);
            blockCount++;
            GameObject blockObject;
            if (blockDirection ==0)
            {
                blockObject = Instantiate(block, new Vector3(6.5f, 0.25f + 0.5f * (blockCount - 1), -0.57f),
                           Quaternion.identity);
            }

            else
            {
                blockObject = Instantiate(block, new Vector3(0.83f, 0.25f + 0.5f * (blockCount - 1), -0.57f),
                           Quaternion.identity);
            }
                       
            blockObject.GetComponent<MeshRenderer>().material = blockMaterial[blockType];
            blockObject.GetComponent<BlockCtrl>().blockDirection = this.blockDirection;
            StartCoroutine("MakeBlockFunc");
            yield return null;
        }

        yield return null;
    }
}
