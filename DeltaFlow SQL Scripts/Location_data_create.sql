USE [Deltaflow_Home]  
GO

SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Location_Data](
	[Loc_Id] [int] IDENTITY(1,1) NOT NULL,
	[Pipe_Id] [int] NOT NULL,
	[Time] [datetime] NOT NULL,
	[Location] [geography] NOT NULL,
	[wake_Con] [bit],
CONSTRAINT [PK_Location_Data] PRIMARY KEY CLUSTERED
(
	[Loc_Id] ASC
),
CONSTRAINT [FK_Location_Data] FOREIGN KEY (Pipe_Id)
	REFERENCES Customer_Data(Pipe_Id)

)
ON [PRIMARY]
GO