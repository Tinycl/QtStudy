#include <QtGui>
#include "histogram.h"

Histogram::Histogram( QWidget* parent ) : QWidget(parent)
{
	m_VecItems.clear( );
}

void Histogram::AddItem( QString name, qreal value,
						 QColor pillarColor )
{
	HistogramItem item;
	item.m_Name			= name;
	item.m_Value		= value;
	item.m_PillarColor	= pillarColor;
	item.m_PillarRect	= QRect( );
	m_VecItems.push_back( item );

    this->update();
}

void Histogram::SetMaxValue( quint32 maxValue )
{
	m_MaxValue = maxValue;
}

void Histogram::Paint( QPaintDevice* pDevice )
{
	QPainter painter( pDevice );
	DrawAxis( pDevice, &painter );
	DrawPillars( pDevice, &painter );
	DrawText( &painter );
	DrawScale( pDevice, &painter );
}

void Histogram::DrawAxis( QPaintDevice* pDevice, QPainter* pPainter )
{
	pPainter->drawLine( yAxisOffset, 0, yAxisOffset, pDevice->height( ) );
	pPainter->drawLine( 0, pDevice->height( ) - xAxisOffset,
						pDevice->width( ), pDevice->height( ) - xAxisOffset );
}

void Histogram::DrawPillars( QPaintDevice* pDevice, QPainter* pPainter )	// 绘制柱子
{
	if ( m_VecItems.size( ) == 0 ) return;

	//const quint32 blankWidth = 64;		// 柱子间空格宽
	quint32 pillarWidth = ( pDevice->width( ) - yAxisOffset - pillarIndent
							- quint32( m_VecItems.size( ) - 1 ) * blankWidth )
			/ m_VecItems.size( );		// 柱子的宽

	// 绘制因子。绘制因子在绘制柱子的时候起着重要作用。
	// 根据比例公式：
	// pDevice->width( ) - xAxisOffset         pillarHeight
	// --------------------------------- = --------------------
	//              MaxValue                m_VecItem[0].value
	// 求出pillarHeight的值，但是左边的部分我们可以看作是一个绘制因子heightFact记录下来。
	// 计算时可以节约时间。
	qreal heightFact = qreal( pDevice->height( ) - xAxisOffset ) / m_MaxValue;

	for ( int i = 0; i < m_VecItems.size( ); ++i )
	{
		quint32 pillarHeight = m_VecItems[i].m_Value * heightFact;
		int leftUpX = yAxisOffset + pillarIndent + i * ( pillarWidth + blankWidth );
		int leftUpY = pDevice->height( ) - xAxisOffset - pillarHeight;
		QRect& rect = m_VecItems[i].m_PillarRect;

		rect.setRect( leftUpX, leftUpY, pillarWidth, pillarHeight );
		pPainter->setPen( QPen( m_VecItems[i].m_PillarColor ) );
		pPainter->setBrush( QBrush( m_VecItems[i].m_PillarColor ) );
		pPainter->drawRect( rect );
	}
}

void Histogram::DrawText( QPainter* pPainter )		// 绘制文字
{
	// 已经可以保证m_VecItems.[i].m_Rect.isNull( )为假
	// 即柱子所在的矩形框是一个有效的矩形框
	pPainter->setPen( QPen( QColor( 0, 0, 0 ) ) );
	for ( int i = 0; i < m_VecItems.size( ); ++i )
	{
		QRect rect( m_VecItems[i].m_PillarRect.left( ) - blankWidth / 2,
					m_VecItems[i].m_PillarRect.top( ) - textRectHeight,
					m_VecItems[i].m_PillarRect.width( ) + blankWidth,
					textRectHeight );

		const QString& text = QString( "%1(%2)" )
				.arg( m_VecItems[i].m_Name ).arg( m_VecItems[i].m_Value );
		pPainter->drawText( rect, Qt::AlignCenter, text );
	}
}

void Histogram::DrawScale( QPaintDevice *pDevice, QPainter *pPainter )		// 绘制刻度
{
	// 名词解释 MSWidth = Marked Scale Width，刻度宽
	// MSHeight = Marked Scale Height 刻度高
	const quint32 MSWidth			= 100;
	const quint32 MSHeight			= textRectHeight;
	const quint32 heightInterval
			= ( pDevice->height( ) - xAxisOffset ) / 4;

	for ( int i = 0; i < 4; ++i )
	{
		QRect rect( 0,
					i * heightInterval,
					MSWidth,
					MSHeight );
		pPainter->drawLine( yAxisOffset - 2,
							i * heightInterval,
							yAxisOffset + 2,
							i * heightInterval );
		pPainter->drawText(
					rect, Qt::AlignLeft, QString( "%1" )
					.arg( m_MaxValue * ( 4 - i ) / 4 ) );
	}

}

void Histogram::Clear()
{
    m_VecItems.clear();
}

void Histogram::paintEvent(QPaintEvent *)
{
    Paint(this);
}







