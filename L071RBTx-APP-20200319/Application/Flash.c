/**
  *********************************************************************************************************
  * @file    gpio.c
  * @author  LockPlate -- ZZF
  * @version V1.0
  * @date    2019-5-15
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "Common.h"
#include "Flash.h"

uint16_t SPI_FLASH_TYPE=W25Q80;//默认就是25Q80
/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SPI_HandleTypeDef FLASHHandle;
FLASH_StatusTypeDef FLASHStatus = FLASH_OK;

/**********************************************************************************************************
 @Function			void FLASH_Init(void)
 @Description		FLASH_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void FLASH_Init(void)
{
	uint16_t ReadDeviceID;
	FLASHStatus = FLASH_OK;
	
  /*##-1- Configure the SPI peripheral #######################################*/
  /* Set the SPI parameters */
  FLASHHandle.Instance               = FLASH_SPI;
  FLASHHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  FLASHHandle.Init.Direction         = SPI_DIRECTION_2LINES;
  FLASHHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  FLASHHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  FLASHHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  FLASHHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  FLASHHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  FLASHHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  FLASHHandle.Init.CRCPolynomial     = 7;
  FLASHHandle.Init.NSS               = SPI_NSS_SOFT;

  FLASHHandle.Init.Mode = SPI_MODE_MASTER;


  if(HAL_SPI_Init(&FLASHHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
	
	for(int nCount = 0;nCount < 3; nCount++){
		ReadDeviceID = SPI_Flash_ReadID();
		if ((ReadDeviceID != FLASH_ID)) {
			FLASHStatus = FLASH_ERROR;
			printf("FLASH_ERROR\r\n");
		}
		else {
			FLASHStatus = FLASH_OK;
			break;
		}
	}
	
	Flash_DeInit();
}

/**********************************************************************************************************
 @Function			void Flash_NSS(void)
 @Description		Flash_NSS
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
FLASH_StatusTypeDef FLASH_Get_Status(void)
{
	return FLASHStatus;
}

/**********************************************************************************************************
 @Function			void Flash_NSS(void)
 @Description		Flash_NSS
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Flash_NSS(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	FLASH_GPIO_CLK_ENABLE();
	FLASH_CLK_ENABLE();

	GPIO_InitStruct.Pin = FLASH_SCK_PIN|FLASH_MISO_PIN|FLASH_MOSI_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = FLASH_GPIO_AF;
	HAL_GPIO_Init(FLASH_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = FLASH_PIN_NSS;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(FLASH_GPIO_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(FLASH_GPIO_PORT, FLASH_PIN_NSS, GPIO_PIN_SET);
	
}

/**********************************************************************************************************
 @Function			void Flash_DeInit(void)
 @Description		Flash_DeInit
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Flash_DeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	FLASH_GPIO_CLK_ENABLE();
	FLASH_CLK_ENABLE();

	GPIO_InitStruct.Pin = FLASH_SCK_PIN|FLASH_MISO_PIN|FLASH_MOSI_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(FLASH_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = FLASH_PIN_NSS;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(FLASH_GPIO_PORT, &GPIO_InitStruct);
	
}

/**********************************************************************************************************
 @Function			void SPI_Flash_ReadID(void)
 @Description		SPI_Flash_ReadID
 @Input				  void
 @Return				void
 @Other:
//读取芯片ID (W25X80的ID:0XEF13) (采用芯片ID：0X1f15)4Mflash(32Mb)
**********************************************************************************************************/
uint16_t SPI_Flash_ReadID(void)
{
	uint16_t Temp = 0; 
	unsigned char g_ucTxBuff[6];
	unsigned char g_ucRxBuff[6];

	g_ucTxBuff[0]=W25X_ManufactDeviceID;
	g_ucTxBuff[1]=0x00;
	g_ucTxBuff[2]=0x00;
	g_ucTxBuff[3]=0x00;
	g_ucTxBuff[4]=0xff;
	g_ucTxBuff[5]=0xff;

	SPI_FLASH_CS_LOW();	//NSS = 0;

	HAL_SPI_TransmitReceive(&FLASHHandle, g_ucTxBuff,g_ucRxBuff, 6, 1000);

	SPI_FLASH_CS_HIGH();	//NSS = 1;	

	Temp|= g_ucRxBuff[4]<<8;
	Temp|= g_ucRxBuff[5];
	   
	return Temp;
}

/**********************************************************************************************************
 @Function			void SPI_Flash_ReadSR(void)
 @Description		SPI_Flash_ReadSR
 @Input				  void
 @Return				uint8_t
 @Other:
//4Kbytes为一个Sector
//16个扇区为1个Block
//W25X16
//容量为2M字节,共有32个Block,512个Sector 

//读取SPI_FLASH的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
**********************************************************************************************************/
uint8_t SPI_Flash_ReadSR(void)   
{  
	uint8_t byte=0; 

	unsigned char g_ucTxBuff[2];
	unsigned char g_ucRxBuff[2];

	g_ucTxBuff[0]=W25X_ReadStatusReg;
	g_ucTxBuff[1]=0xFF;
	g_ucRxBuff[1] = 0x00;
  
	SPI_FLASH_CS_LOW();                            //使能器件   
	
	HAL_SPI_TransmitReceive(&FLASHHandle, g_ucTxBuff,g_ucRxBuff, 2, 1000);

	byte = g_ucRxBuff[1];
	SPI_FLASH_CS_HIGH();                            //取消片选     
	return byte;   
} 

/**********************************************************************************************************
 @Function			void SPI_FLASH_Write_SR(void)
 @Description		SPI_FLASH_Write_SR
 @Input				  void
 @Return				void
 @Other:
//写SPI_FLASH状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
**********************************************************************************************************/
void SPI_FLASH_Write_SR(uint8_t sr)   
{   
	unsigned char g_ucTxBuff[2];
	unsigned char g_ucRxBuff[2];

	g_ucTxBuff[0]=W25X_WriteStatusReg;
	g_ucTxBuff[1]=sr;
	
	SPI_FLASH_CS_LOW();                            //使能器件   
	
	HAL_SPI_TransmitReceive(&FLASHHandle, g_ucTxBuff,g_ucRxBuff, 2, 1000);
	
//	SPI1_ReadWriteByte(W25X_WriteStatusReg);   //发送写取状态寄存器命令    
//	SPI1_ReadWriteByte(sr);               //写入一个字节  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
}   

/**********************************************************************************************************
 @Function			void SPI_FLASH_Write_SR(void)
 @Description		SPI_FLASH_Write_SR
 @Input				  void
 @Return				void
 @Other:
//SPI_FLASH写使能	
//将WEL置位  
**********************************************************************************************************/
void SPI_FLASH_Write_Enable(void)   
{
	unsigned char g_ucTxBuff[1];
	unsigned char g_ucRxBuff[1];

	g_ucTxBuff[0]=W25X_WriteEnable;

	SPI_FLASH_CS_LOW();                            //使能器件   
	
	HAL_SPI_TransmitReceive(&FLASHHandle, g_ucTxBuff,g_ucRxBuff, 1, 1000);
	
//    SPI1_ReadWriteByte(W25X_WriteEnable);      //发送写使能  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
} 

/**********************************************************************************************************
 @Function			void SPI_FLASH_Write_Disable(void)
 @Description		SPI_FLASH_Write_Disable
 @Input				  void
 @Return				void
 @Other:
//SPI_FLASH写禁止	
//将WEL清零  
**********************************************************************************************************/
void SPI_FLASH_Write_Disable(void)   
{  
	unsigned char g_ucTxBuff[1];
	unsigned char g_ucRxBuff[1];

	g_ucTxBuff[0]=W25X_WriteDisable;

	SPI_FLASH_CS_LOW();                            //使能器件   
	
	HAL_SPI_TransmitReceive(&FLASHHandle, g_ucTxBuff,g_ucRxBuff, 1, 1000);
 
//    SPI1_ReadWriteByte(W25X_WriteDisable);     //发送写禁止指令    
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
} 			    

/**********************************************************************************************************
 @Function			void SPI_Flash_Read(void)
 @Description		SPI_Flash_Read
 @Input				  void
 @Return				void
 @Other:
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
**********************************************************************************************************/
void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{  
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}
	
	unsigned char g_ucTxBuff[4];
	unsigned char g_ucRxBuff[4];

	g_ucTxBuff[0]=W25X_ReadData;
	g_ucTxBuff[1]=((ReadAddr & 0xFF0000) >> 16);
	g_ucTxBuff[2]=((ReadAddr & 0xFF00) >> 8);
	g_ucTxBuff[3]=(ReadAddr & 0xFF);
	
	SPI_FLASH_CS_LOW();                            //使能器件   
	
	HAL_SPI_TransmitReceive(&FLASHHandle, g_ucTxBuff,g_ucRxBuff, 4, 1000);
 
	HAL_SPI_Receive(&FLASHHandle, pBuffer,NumByteToRead, 1000);
	
//  for(i=0;i<NumByteToRead;i++)
//	{ 
//		HAL_SPI_Receive(&FLASHHandle, &pBuffer[i],1, 1000);   //循环读数  
//  }
	
//    SPI1_ReadWriteByte(W25X_ReadData);         //发送读取命令   
//    SPI1_ReadWriteByte((uint8_t)((ReadAddr)>>16));  //发送24bit地址    
//    SPI1_ReadWriteByte((uint8_t)((ReadAddr)>>8));   
//    SPI1_ReadWriteByte((uint8_t)ReadAddr);   
//    for(i=0;i<NumByteToRead;i++)
//	{ 
//        pBuffer[i]=SPI1_ReadWriteByte(0XFF);   //循环读数  
//    }
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
}  

/**********************************************************************************************************
 @Function			void SPI_Flash_Write_Page(void)
 @Description		SPI_Flash_Write_Page
 @Input				  void
 @Return				void
 @Other:
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	
**********************************************************************************************************/
void SPI_Flash_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}
	unsigned char g_ucTxBuff[4];
	unsigned char g_ucRxBuff[4];

	g_ucTxBuff[0]=W25X_PageProgram;
	g_ucTxBuff[1]=((WriteAddr & 0xFF0000) >> 16);
	g_ucTxBuff[2]=((WriteAddr & 0xFF00) >> 8);
	g_ucTxBuff[3]=(WriteAddr & 0xFF);

  SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_FLASH_CS_LOW();                            //使能器件  

	HAL_SPI_TransmitReceive(&FLASHHandle, g_ucTxBuff,g_ucRxBuff, 4, 1000);
	HAL_SPI_Transmit(&FLASHHandle, pBuffer,NumByteToWrite, 1000);
//    SPI1_ReadWriteByte(W25X_PageProgram);      //发送写页命令   
//    SPI1_ReadWriteByte((uint8_t)((WriteAddr)>>16)); //发送24bit地址    
//    SPI1_ReadWriteByte((uint8_t)((WriteAddr)>>8));   
//    SPI1_ReadWriteByte((uint8_t)WriteAddr);   
//    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]);//循环写数  
	SPI_FLASH_CS_HIGH();                            //取消片选 
	SPI_Flash_Wait_Busy();					   //等待写入结束
}

/**********************************************************************************************************
 @Function			void SPI_Flash_Write_Page(void)
 @Description		SPI_Flash_Write_Page
 @Input				  void
 @Return				void
 @Other:
//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
**********************************************************************************************************/
void SPI_Flash_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 			 		 
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}

	uint16_t pageremain;	   
	pageremain=256-WriteAddr%256; //单页剩余的字节数		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
	while(1)
	{	   
		SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//写入结束了
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
			if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
			else pageremain=NumByteToWrite; 	  //不够256个字节了
		}
	};	    
} 

/**********************************************************************************************************
 @Function			void SPI_Flash_Write(void)
 @Description		SPI_Flash_Write
 @Input				  void
 @Return				void
 @Other:
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)  
**********************************************************************************************************/
uint8_t SPI_FLASH_BUF[4096];
void SPI_Flash_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 	
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}
	
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    

	secpos=WriteAddr/4096;//扇区地址 0~511 for w25x16
	secoff=WriteAddr%4096;//在扇区内的偏移
	secremain=4096-secoff;//扇区剩余空间大小   

	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//不大于4096个字节
	while(1) 
	{	
		SPI_Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			SPI_Flash_Erase_Sector(secpos);//擦除这个扇区
			for(i=0;i<secremain;i++)	   //复制
			{
				SPI_FLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);//写入整个扇区  

		}else 
		{
			SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);//写已经擦除了的,直接写入扇区剩余区间. 		
		}			
		if(NumByteToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;//扇区地址增1
			secoff=0;//偏移位置为0 	 

		   	pBuffer+=secremain;  //指针偏移
				WriteAddr+=secremain;//写地址偏移	   
		   	NumByteToWrite-=secremain;				//字节数递减
			if(NumByteToWrite>4096)secremain=4096;	//下一个扇区还是写不完
			else secremain=NumByteToWrite;			//下一个扇区可以写完了
		}	 
	};	 	 
}

/**********************************************************************************************************
 @Function			void SPI_Flash_Erase_Chip(void)
 @Description		SPI_Flash_Erase_Chip
 @Input				  void
 @Return				void
 @Other:
//擦除整个芯片
//整片擦除时间:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//等待时间超长...  
**********************************************************************************************************/
void SPI_Flash_Erase_Chip(void)   
{                                             
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}
	SPI_FLASH_Write_Enable();                  //SET WEL 
	SPI_Flash_Wait_Busy();   
	SPI_FLASH_CS_LOW();                            //使能器件 
	HAL_SPI_Transmit(&FLASHHandle, (uint8_t*)W25X_ChipErase,1, 1000);
//    SPI1_ReadWriteByte(W25X_ChipErase);        //发送片擦除命令  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
	SPI_Flash_Wait_Busy();   				   //等待芯片擦除结束
} 

/**********************************************************************************************************
 @Function			void SPI_Flash_Erase_Chip(void)
 @Description		SPI_Flash_Erase_Chip
 @Input				  void
 @Return				void
 @Other:
//擦除一个扇区
//Dst_Addr:扇区地址 0~511 for w25x16
//擦除一个山区的最少时间:150ms 
**********************************************************************************************************/
void SPI_Flash_Erase_Sector(uint32_t Dst_Addr)   
{   
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}
	unsigned char g_ucTxBuff[4];
	unsigned char g_ucRxBuff[4];

//	//监视falsh擦除情况,测试用   
// 	printf("fe:%x\r\n",Dst_Addr);	

	Dst_Addr*=4096;

	g_ucTxBuff[0]=W25X_SectorErase;
	g_ucTxBuff[1]=((uint8_t)((Dst_Addr)>>16));
	g_ucTxBuff[2]=((uint8_t)((Dst_Addr)>>8));
	g_ucTxBuff[3]=((uint8_t)Dst_Addr); 

	SPI_FLASH_Write_Enable();                  //SET WEL 	 
	SPI_Flash_Wait_Busy();   
	SPI_FLASH_CS_LOW();                            //使能器件   

	HAL_SPI_TransmitReceive(&FLASHHandle, g_ucTxBuff,g_ucRxBuff, 4, 1000);

//    SPI1_ReadWriteByte(W25X_SectorErase);      //发送扇区擦除指令 
//    SPI1_ReadWriteByte((uint8_t)((Dst_Addr)>>16));  //发送24bit地址    
//    SPI1_ReadWriteByte((uint8_t)((Dst_Addr)>>8));   
//    SPI1_ReadWriteByte((uint8_t)Dst_Addr);  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
	SPI_Flash_Wait_Busy();   				   //等待擦除完成
}  

/**********************************************************************************************************
 @Function			void SPI_Flash_Wait_Busy(void)
 @Description		SPI_Flash_Wait_Busy
 @Input				  void
 @Return				void
 @Other:
//等待空闲
**********************************************************************************************************/
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
} 

/**********************************************************************************************************
 @Function			void SPI_Flash_PowerDown(void)
 @Description		SPI_Flash_PowerDown
 @Input				  void
 @Return				void
 @Other:
//进入掉电模式
**********************************************************************************************************/
void SPI_Flash_PowerDown(void)   
{ 
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}
	
	SPI_FLASH_CS_LOW();                            //使能器件 
	HAL_SPI_Transmit(&FLASHHandle,(uint8_t*)W25X_PowerDown,1, 1000);
//    SPI1_ReadWriteByte(W25X_PowerDown);        //发送掉电命令  
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
//    delay_us(3);  //等待TPD  
}  

/**********************************************************************************************************
 @Function			void SPI_Flash_WAKEUP(void)
 @Description		SPI_Flash_WAKEUP
 @Input				  void
 @Return				void
 @Other:
//唤醒
**********************************************************************************************************/
void SPI_Flash_WAKEUP(void)   
{  
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}
	
	SPI_FLASH_CS_LOW();                            //使能器件 
	HAL_SPI_Transmit(&FLASHHandle,(uint8_t*)W25X_ReleasePowerDown,1, 1000);  
//    SPI1_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	SPI_FLASH_CS_HIGH();                            //取消片选     	      
//    delay_us(3);                               //等待TRES1
}   

/********************************************** END OF FLEE **********************************************/
