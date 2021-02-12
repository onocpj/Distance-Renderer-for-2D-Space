#pragma once

#include <memory>
#include <string>
#include <vector>

#include "DataTypes.h"
#include "Shapes.h"
#include "UDT.h"

/*test*/
#include <windows.h>
#include <wingdi.h>
/*test*/

#define INIT_RENDER_SECTION_KEY		0
#define	MIN_MAP_SIZE			100.0f
#define MIN_RADIUS			1.0f
#define RENDERING_GRID_DIM		{ 60, 60 }
#define MAX_RENDER_DISTANCE		5000.0f
#define PRELOAD_RENDER_DISTANCE_OFFSET	20.0f	

namespace Strave {


	class GameObject2D;


	namespace Renderer {

		class RenderingConstraints {

		public:
			inline RenderingConstraints()
				: m_InitPoint(UNDEF_VECTOR2F), m_RenderRadius(UNDEF_FLOAT), m_PreloadRadius(UNDEF_FLOAT)
			{}
			inline RenderingConstraints(const Vector2f& initPoint, float renderingRadius, float preloadRadius)
				: m_InitPoint(initPoint), m_RenderRadius(VerifyRenderingRadius(renderingRadius)), m_PreloadRadius(preloadRadius)
			{}
			inline ~RenderingConstraints() {}

			inline void SetInitPoint(const Vector2f& initPoint) { m_InitPoint = initPoint; }
			inline void SetRenderingRadius(float radius) { m_RenderRadius = VerifyRenderingRadius(radius); }
			inline void SetPreloadRadius(float radius) { m_PreloadRadius = radius; }
			inline const Vector2f& GetPoint(void) const { return m_InitPoint; }
			inline const float& GetRenderRadius(void) const { return m_RenderRadius; }
			inline const float& GetPreloadedRadius(void) const { return m_PreloadRadius; }

		private:
			inline float VerifyRenderingRadius(float renderingRadius) { return renderingRadius <= m_PreloadRadius ? renderingRadius : m_PreloadRadius; }


			Vector2f	m_InitPoint;
			float		m_RenderRadius;
			float		m_PreloadRadius;

		};
		class DistanceRendering {
		
		private:
			class Segment;
			class RenderSection;
			
			typedef int32_t SegmentKey_t;

		public:
			DistanceRendering(RenderingConstraints& constraints, const std::vector<GameObject2D*>& go2dCon, const Vector2v2f& normMapPoints);
			~DistanceRendering();

			void ShowSegmentContent(void) const;
			static Vector2v2f GetHighestPoints(const std::vector<GameObject2D*>& go2dCon);
			inline std::shared_ptr<RenderSection> GetRenderSection(void) { return m_RenderSection; };

		private:
			class RenderSection {

			private:
				typedef std::vector<GameObject2D*>			GO2DList_t;
				typedef std::vector<std::shared_ptr<Segment>>		RenderGrid_t;
				typedef std::vector<std::shared_ptr<Segment>>*		GridReference_t;

				typedef std::vector<std::shared_ptr<Segment>>::iterator	Grid_iter;
				typedef std::vector<GameObject2D*>::iterator		GO2DList_iter;

				typedef struct ComplexGrid {

					inline ComplexGrid()
						: InRange(std::make_shared<RenderGrid_t>()),
						NotInRange(std::make_shared<RenderGrid_t>())
					{}
					inline ~ComplexGrid() {}

					std::shared_ptr<RenderGrid_t> InRange;
					std::shared_ptr<RenderGrid_t> NotInRange;

				} ComplexGrid_t;
				typedef struct RenderBuffer {

					inline RenderBuffer()
						: Preloaded(std::make_shared<GO2DList_t>()),
						Loaded(Preloaded)
					{}
					inline ~RenderBuffer() {}
					
					std::shared_ptr<GO2DList_t> Preloaded;
					std::shared_ptr<GO2DList_t> Loaded;

				} RenderBuffer_t;
				typedef struct RenderingArea {

					Strave::Shapes::Circle RenderArea;
					Strave::Shapes::Circle PreloadArea;

				} RenderingArea_t;

			public:
				RenderSection(RenderingConstraints& constraints, const std::vector<std::shared_ptr<Segment>>& grid);
				~RenderSection();

				/* test */ void DrawRenderGrid(const HDC& hdc);
				/* test */ void CreatePoint(const HDC& hdc, int x, int y, COLORREF color);

				inline void SetRenderDistance(float radius) {

					if (radius >= MIN_RADIUS)
						m_PreloadRenderDistance = radius;

				}

				inline std::shared_ptr<GO2DList_t>& GetObjectsToRender(void) {

					return m_RenderingBuffer->Loaded;

				}
				inline const Vector2f& GetPointPosition(void) const { return m_RenderingArea.RenderArea.GetPostion(); };
				inline const Vector2f& GetCenterPoint(void) const { return m_RenderingArea.PreloadArea.GetPostion(); };
				inline const std::vector<GameObject2D*>& GetObjectContainer(const Segment& seg) const { return *seg.m_GO2DReferenceContainer; }
				std::shared_ptr<RenderGrid_t> GetRenderArea(void) const;

				inline void UpdatePointPosition(const Vector2f& pointPosition) { m_RenderingArea.RenderArea.SetPosition(pointPosition); }
				void Render(const HDC& hdc);	// runtime function
				void Update(void);		// runtime function)										

			private:
				void Init(RenderingConstraints& constraints, const std::vector<std::shared_ptr<Segment>>& grid);
				void PreloadRenderingGrid(void);
				float VerifyRadius(float radius) const;
				float GetPreloadRenderOffset(void) const;
				void OptimizedUpdate(void);	// runtime function											
				void RawUpdate(void);		// runtime function		
		

				float				m_PreloadRenderOffset;
				float				m_PreloadRenderDistance;
				float				m_RenderDistance;
				GridReference_t			m_GridReference;
				RenderingArea_t			m_RenderingArea;
				std::shared_ptr<ComplexGrid_t>	m_RenderingGrid;
				std::shared_ptr<RenderBuffer_t>	m_RenderingBuffer;
			};
			class Segment {

			public:
				Segment(SegmentKey_t key, const Vector2f& size, const Vector2f& pos, const std::vector<GameObject2D*>& go2dSegCon);
				~Segment();

				void ShowContainerContent(void) const;
				inline unsigned int GetContainerSize() { return m_ContainerSize; }
				inline int GetKey(void) const { return m_Key; }
				inline const Vector2f& GetCenterPoint(void) const { return m_CenterPoint; };
				inline const Vector2f& GetSize(void) const { return m_Size; }
				inline const Vector2f& GetPosition(void) const { return m_Position; }
				inline bool IsOccupied(void) const { return m_OccupancyState; };

			private:
				void Init(const std::vector<GameObject2D*>& go2dSegCon);
				Vector2f InitCenterPoint(const Vector2f& pos, const Vector2f& size) const;

				friend const std::vector<GameObject2D*>& RenderSection::GetObjectContainer(const Segment& seg) const;


				bool				m_OccupancyState;
				unsigned int			m_ContainerSize;
				SegmentKey_t			m_Key;
				Vector2f			m_Size;
				Vector2f			m_Position;
				Vector2f			m_CenterPoint;
				std::vector<GameObject2D*>* 	m_GO2DReferenceContainer;

			};

			void Init(RenderingConstraints& constraints, const std::vector<GameObject2D*>& go2dCon);
			std::vector<GameObject2D*>* GetObjectsInSegmentRange(const Vector2f& segPos, const Vector2f& segSize, std::vector<GameObject2D*>& unassignedObjects);
			void CreateSegments(void);
			Vector2f GetMapSize(void) const;


			Vector2u				m_NumberOfFields;
			Vector2v2f				m_NormalizedMapPoints;
			Vector2f				m_MapSize;
			std::vector<std::shared_ptr<Segment>>	m_Grid;
			std::shared_ptr<RenderSection>		m_RenderSection;
			std::vector<GameObject2D*>*		m_GO2DContainerReference;

		};

	}

}

