#pragma once
#include <list>
#include <unordered_map>
#include <functional>
#include "food.h"
#include "../../../common/enums.h"
#include "../../../model/level/level_manager.h"
#include "../flame/flame_manager.h"
#include "../../card/card.h"
#include "../../../common/draw_item.h"
class Food;

class FoodManager
{
private:
    std::vector<std::vector<bool> > map_grids; // 用于指示地图上某格是否放有食物
    std::list<Food *> food_list; // 所有放在地图上的食物
    std::vector<Card *> card_vec; // 所有供放置的食物卡片
//    LevelManager *level_manager;
    LevelManager *level_manager;
    FlameManager *flame_manager;

// properties
//  绘图用
//    std::list<DrawItem *> draw_foodlist;
    std::shared_ptr<std::list<DrawItem *>> draw_foodlist_ptr;
    std::shared_ptr<std::vector<DrawItem *>> draw_card_vec_ptr;
    std::shared_ptr<std::vector<float *>> draw_card_mask_vec_ptr;
    std::shared_ptr<std::vector<int>> draw_card_cost_vec_ptr;

//    std::shared_ptr<std::unordered_map<FoodType, std::vector<QPixmap *>>> img_dict_ptr; // 从level_manager处绑定
//    std::shared_ptr<std::vector<FoodType>> food_select_vec_ptr;

// command
    std::function<std::pair<int, int>(int row_index, int column_index)> Matrix2Viewport;
    std::function<std::pair<int, int>(int x, int y)> Viewport2Matrix;
    std::function<std::pair<int, int>(int select_index)> Index2Viewport;

public:
    /*** 
     * 控制所有放下的食物
     * @param {int} row_count 关卡地图的行数
     * @param {int} column_count 关卡地图的列数
     */    
    FoodManager(int row_count, int column_count, LevelManager *level_manager, FlameManager *flame_manager);

    void Init();
    /*** 
     * 销毁所有的食物
     */    
    ~FoodManager();
    /*** 
     * 更新所有食物的图片及行为
     */    
//    void UpdateFood();

    /*** 
     * 判断该位置是否为空，空则放置食物并返回true，否则返回false 
     * 卡片是否冷却中不由该函数判断
     */
//    bool PlaceFood(int row_index, int column_index, FoodType food_type);

    /*** 
     * 移除食物（铲子）
     */    
//    void RemoveFood(int row_index, int column_index);

// properties
//    std::shared_ptr<std::list<DrawItem *>> get_DrawFoodList() {return std::make_shared<std::list<DrawItem *>>(draw_foodlist);}
    std::shared_ptr<std::list<DrawItem *>> get_DrawFoodList() { return draw_foodlist_ptr; }
    std::shared_ptr<std::vector<DrawItem *>> get_DrawCardVec() { return draw_card_vec_ptr; }
    std::shared_ptr<std::vector<float *>> get_DrawCardMaskVec() { return draw_card_mask_vec_ptr; }
    std::shared_ptr<std::vector<int>> get_DrawCardCostVec() { return draw_card_cost_vec_ptr; }

    void attach_LevelManager(LevelManager *p_level_manager) { level_manager = p_level_manager; }

// command
    std::function<bool(int row_index, int column_index, int select_index)> get_PlaceFoodCommand();
    std::function<void()> get_UpdateFoodCommand();
    std::function<void()> get_UpdateCardCommand();
    std::function<void(int row_index, int column_index)> get_RemoveFoodCommand();

//
    void attach_Matrix2ViewportCommand(std::function<std::pair<int, int>(int row_index, int column_index)>&& func) { Matrix2Viewport = std::move(func); }
    void attach_Viewport2MatrixCommand(std::function<std::pair<int, int>(int x, int y)>&& func) { Viewport2Matrix = std::move(func); }
    void attach_Index2ViewportCommand(std::function<std::pair<int, int>(int select_index)>&& func) { Index2Viewport = std::move(func); }
};
