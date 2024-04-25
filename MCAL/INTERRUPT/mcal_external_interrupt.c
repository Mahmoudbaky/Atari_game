/* 
 * File:   mcal_external_interrupt.c
 * Author: houda
 *
 * Created on February 26, 2024, 6:15 PM
 */

#include "mcal_external_interrupt.h"

/* FUNTIONS DECLARATIONS */

/* Pointer to function to hold the callbacks for INTx */
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;


/* helper functions for INTx */
static Std_ReturnType Interrupt_INTx_Enable       (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable      (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init    (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init     (const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag   (const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_Choose_Handler_INTx(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INT0_MoveAddressFromStruct (void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INT1_MoveAddressFromStruct (void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INT2_MoveAddressFromStruct (void (*InterruptHandler)(void));

////////////////////////////////////////////////////////////////////////////////
/* Pointer to function to hold the callbacks for RBx */
static InterruptHandler RB4_InterruptHandler_HIGH = NULL;
static InterruptHandler RB4_InterruptHandler_LOW  = NULL;
static InterruptHandler RB5_InterruptHandler_HIGH = NULL;
static InterruptHandler RB5_InterruptHandler_LOW  = NULL;
static InterruptHandler RB6_InterruptHandler_HIGH = NULL;
static InterruptHandler RB6_InterruptHandler_LOW  = NULL;
static InterruptHandler RB7_InterruptHandler_HIGH = NULL;
static InterruptHandler RB7_InterruptHandler_LOW  = NULL;

/* helper functions for RBx */

static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_Choose_Handler_RBx(const interrupt_RBx_t *int_obj);



/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init  (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; 
    }
    else{
        /* Disable the External interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External interrupt did not occur */
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External interrupt edge */
        ret = Interrupt_INTx_Edge_Init(int_obj);
        
        #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
        /* Configure External interrupt Priority */
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif

        /* Configure External interrupt I/O pin */
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        ret = Interrupt_Choose_Handler_INTx(int_obj);
        /* Enable the External interrupt */ 
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}


void INT0_ISR (void){
    /* The INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    /*   code    */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
    else{ /* Nothing */ }
}

void INT1_ISR (void){
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    /*   code    */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
    else{ /* Nothing */ }
}

void INT2_ISR (void){
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    /*   code    */
    
    /* Application Callback function gets called every time this ISR executes */
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
    else{ /* Nothing */ }
}

/***************helper functions for INTx**************/

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
                    INTERRUPT_globalInterruptEnableHigh();
                #else
                INTERRUPT_globalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
                INTERRUPT_InterruptPriorityEnable();
                if (INTERRUPT_LOW_PRIORITY  == int_obj->priority){
                    INTERRUPT_globalInterruptEnableLow();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_globalInterruptEnableHigh();
                }
                else {/* nothing */}
                #else
                INTERRUPT_globalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif

                EXT_INT1_InterruptEnable();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                #if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
                INTERRUPT_InterruptPriorityEnable();
                if (INTERRUPT_LOW_PRIORITY  == int_obj->priority){
                    INTERRUPT_globalInterruptEnableLow();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_globalInterruptEnableHigh();
                }
                else {/* nothing */}
                #else
                INTERRUPT_globalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT2_InterruptEnable();
                break;
            default : ret = E_NOT_OK ;
        }
    }
    return ret;
}    

static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptDisable();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptDisable();
                break; 
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1:
                if     (INTERRUPT_LOW_PRIORITY  == int_obj->priority){EXT_INT1_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT1_HighPrioritySet();}
                else                                                 {/* nothing */}
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                if     (INTERRUPT_LOW_PRIORITY  == int_obj->priority){EXT_INT2_LowPrioritySet();}
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT2_HighPrioritySet();}
                else                                                 {/* nothing */}
                break;   
        }
    }
    return ret;
}
#endif

static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
    switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                if     (INTERRUPT_FALLING_EDGE  == int_obj->edge){EXT_INT0_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE   == int_obj->edge){EXT_INT0_RisingEdgeSet();}
                else                                                 {/* nothing */}
                break;    
            case INTERRUPT_EXTERNAL_INT1:
                if     (INTERRUPT_FALLING_EDGE   == int_obj->edge){EXT_INT1_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT1_RisingEdgeSet();}
                else                                                 {/* nothing */}
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                if     (INTERRUPT_FALLING_EDGE  == int_obj->edge){EXT_INT2_FallingEdgeSet();}
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT2_RisingEdgeSet();}
                else                                                 {/* nothing */}
                break;   
            default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        ret = gpio_pin_direction_initialization(&(int_obj->mcu_pin));
    }
    return ret;
} 

static Std_ReturnType Interrupt_INTx_Clear_Flag   (const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptFlagClear();
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptFlagClear();
                break;
            default : ret = E_NOT_OK ;    
        }
    }
    return ret;
}

static Std_ReturnType Interrupt_INT0_MoveAddressFromStruct (void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_INT1_MoveAddressFromStruct (void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_INT2_MoveAddressFromStruct (void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static Std_ReturnType Interrupt_Choose_Handler_INTx(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                ret = Interrupt_INT0_MoveAddressFromStruct(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                ret = Interrupt_INT1_MoveAddressFromStruct(int_obj->EXT_InterruptHandler);
                break;    
            case INTERRUPT_EXTERNAL_INT2:
                ret = Interrupt_INT2_MoveAddressFromStruct(int_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOT_OK ;
        }
    }
    return ret;
}

/***************helper functions for INTx**************/

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init   (const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        /* This routine clears the interrupt disable for the external interrupt RBx */
        EXT_RBx_InterruptDisable();
        /* This routine clears the interrupt flag for the external interrupt RBx */
        EXT_RBx_InterruptFlagClear();
        /* priority configuration */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
        ret = Interrupt_RBx_Priority_Init(int_obj);
#else
        INTERRUPT_globalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        /* Initialize the RBx pin to be input */
        ret = gpio_pin_direction_initialization(&(int_obj->mcu_pin));
        /* Initialize the call back functions */
        ret = Interrupt_Choose_Handler_RBx(int_obj);
        /* This routine sets the interrupt enable for the external interrupt RBx */
        EXT_RBx_InterruptEnable();
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit (const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
         /* This routine clears the interrupt disable for the external interrupt, RBx */
        EXT_RBx_InterruptDisable();
        /* This routine clears the interrupt flag for the external interrupt, RBx */
        EXT_RBx_InterruptFlagClear();
    }
    return ret;
}


void RB4_ISR(uint8 RB4_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB4_Source){
        if(RB4_InterruptHandler_HIGH){ RB4_InterruptHandler_HIGH(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB4_Source){
        if(RB4_InterruptHandler_LOW){ RB4_InterruptHandler_LOW(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
}

void RB5_ISR(uint8 RB5_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB5_Source){
        if(RB5_InterruptHandler_HIGH){ RB5_InterruptHandler_HIGH(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB5_Source){
        if(RB5_InterruptHandler_LOW){ RB5_InterruptHandler_LOW(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }
}

void RB6_ISR(uint8 RB6_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB6_Source){
        if(RB6_InterruptHandler_HIGH){ RB6_InterruptHandler_HIGH(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB6_Source){
        if(RB6_InterruptHandler_LOW){ RB6_InterruptHandler_LOW(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
}

void RB7_ISR(uint8 RB7_Source){
    /* The RB4 external OnChange interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : To be executed from MCAL Interrupt Context */
    
    /* Application Callback function gets called every time this ISR executes */
    if(0 == RB7_Source){
        if(RB7_InterruptHandler_HIGH){ RB7_InterruptHandler_HIGH(); }
        else{ /* Nothing */ }
    }
    else if (1 == RB7_Source){
        if(RB7_InterruptHandler_LOW){ RB7_InterruptHandler_LOW(); }
        else{ /* Nothing */ }
    }
    else { /* Nothing */ }   
}

/***************helper functions for RBx**************/

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        INTERRUPT_InterruptPriorityEnable();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            INTERRUPT_globalInterruptEnableLow();
            EXT_RBx_Priority_Low(); 
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
            INTERRUPT_globalInterruptEnableHigh();
            EXT_RBx_Priority_High();
        }
        else {/*nothing*/}
    }
    return ret;
}
#endif

static Std_ReturnType Interrupt_Choose_Handler_RBx(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        switch(int_obj->mcu_pin.pin){
            case PIN_4 : 
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case PIN_5 : 
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case PIN_6 : 
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case PIN_7 : 
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}

/***************helper functions for RBx**************/
