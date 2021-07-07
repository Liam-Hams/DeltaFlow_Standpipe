USE [Deltaflow_Home]  
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Flow_Data](
	[Flow_Id] [int] IDENTITY(1,1) NOT NULL,
	[Loc_Id] [int] NOT NULL,
	[Usage_Latest] [decimal](18,4) NOT NULL,
	[Usage_Total] [decimal](18,4) NOT NULL,
CONSTRAINT [PK_Flow_Data] PRIMARY KEY CLUSTERED
(
	[Flow_Id] ASC
),
CONSTRAINT [FK_Flow_Data] FOREIGN KEY (Loc_Id)
	REFERENCES Location_Data(Loc_Id)

)
ON [PRIMARY]
GO