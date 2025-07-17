using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour
{
    private float horizontalInput;
    private float verticalInput;
    private bool isGrounded;
    private bool spacePressed;
    private Rigidbody rigidbodyComponent;

    public float mouseSensitivity = 100f;

    void Start()
    {
        rigidbodyComponent = GetComponent<Rigidbody>();
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }

    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Space))
        {
            spacePressed = true;
        }
        horizontalInput = Input.GetAxis("Horizontal");
        verticalInput = Input.GetAxis("Vertical");
        float mouseX = Input.GetAxis("Mouse X") * mouseSensitivity * Time.deltaTime;
        transform.Rotate(Vector3.up * mouseX);
    }

    private void FixedUpdate()
    {
        Vector3 moveDirection = transform.forward * verticalInput + transform.right * horizontalInput;

        if (moveDirection.magnitude > 1f)
            moveDirection = moveDirection.normalized;

        float speed = 3f;
        Vector3 horizontalVelocity = moveDirection * speed;

        float verticalVelocity = rigidbodyComponent.velocity.y;

        if (horizontalInput == 0 && verticalInput == 0)
        {
            horizontalVelocity = Vector3.zero;
        }

        rigidbodyComponent.velocity = new Vector3(horizontalVelocity.x, verticalVelocity, horizontalVelocity.z);

        if (!isGrounded)
            return;

        if (spacePressed)
        {
            rigidbodyComponent.AddForce(Vector3.up * 5, ForceMode.VelocityChange);
            spacePressed = false;
        }
    }

    private void OnCollisionEnter(Collision col)
    {
        isGrounded = true;
    }

    private void OnCollisionExit(Collision col)
    {
        isGrounded = false;
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.layer == 6)
        {
            Destroy(other.gameObject);
        }
    }
}
