#include "coach.h"
#include "core/constants.h"
#include "entities/ball.h"
#include "entities/team.h"
#include "game/scene.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

//data types
typedef struct Box{

    float left;
    float right;
    float top;
    float bottom;

} Box;

typedef struct Movement_Rules{

    Vec2 attack_position;
    Vec2 defend_position;

    Box box;

} Movement_Rules;

//constants
#define LEFT_LINE  PITCH_X
#define RIGHT_LINE (PITCH_X + PITCH_W)
#define TOP_LINE PITCH_Y
#define BOTTOM_LINE (PITCH_Y + PITCH_H)

float SHOOTING_REDUCE = 200;

//VERTICAL_LINE & HORIZONTAL_LINE
#define VERTICAL_LINE(n, m)   (LEFT_LINE + (RIGHT_LINE - LEFT_LINE) * ((float)(m)/(float)(n)))
#define HORIZONTAL_LINE(n, m) (TOP_LINE + (BOTTOM_LINE - TOP_LINE) * ((float)(m)/(float)(n)))

//Movement Rules 
Movement_Rules movement_rules_team_1[6] = {
    {
        .attack_position = {
            .x = VERTICAL_LINE(6, 4),
            .y = HORIZONTAL_LINE(2, 1)
        },
        .defend_position = {
            .x = VERTICAL_LINE(2, 1),
            .y = HORIZONTAL_LINE(2, 1)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 1),
            .right  = VERTICAL_LINE(2, 2),
            .top    = HORIZONTAL_LINE(6, 2),
            .bottom = HORIZONTAL_LINE(6, 4)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(6, 5),
            .y = HORIZONTAL_LINE(6, 2)
        },
        .defend_position = {
            .x = VERTICAL_LINE(6, 4),
            .y = HORIZONTAL_LINE(4, 1)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 1),
            .right  = VERTICAL_LINE(2, 2),
            .top    = HORIZONTAL_LINE(6, 0),
            .bottom = HORIZONTAL_LINE(6, 2)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(6, 5),
            .y = HORIZONTAL_LINE(6, 4)
        },
        .defend_position = {
            .x = VERTICAL_LINE(6, 4),
            .y = HORIZONTAL_LINE(4, 3)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 1),
            .right  = VERTICAL_LINE(2, 2),
            .top    = HORIZONTAL_LINE(6, 4),
            .bottom = HORIZONTAL_LINE(6, 6)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(2, 1),
            .y = HORIZONTAL_LINE(4, 1)
        },
        .defend_position = {
            .x = VERTICAL_LINE(4, 1),
            .y = HORIZONTAL_LINE(4, 1)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 0),
            .right  = VERTICAL_LINE(2, 1),
            .top    = HORIZONTAL_LINE(2, 0),
            .bottom = HORIZONTAL_LINE(2, 1)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(2, 1),
            .y = HORIZONTAL_LINE(4, 3)
        },
        .defend_position = {
            .x = VERTICAL_LINE(4, 1),
            .y = HORIZONTAL_LINE(4, 3)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 0),
            .right  = VERTICAL_LINE(2, 1),
            .top    = HORIZONTAL_LINE(2, 1),
            .bottom = HORIZONTAL_LINE(2, 2)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(12, 1),
            .y = HORIZONTAL_LINE(2, 1)
        },
        .defend_position = {
            .x = VERTICAL_LINE(24, 1),
            .y = HORIZONTAL_LINE(2, 1)
        },
        .box = {
            .left   = VERTICAL_LINE(6, 0),
            .right  = VERTICAL_LINE(12, 1),
            .top    = HORIZONTAL_LINE(6, 2),
            .bottom = HORIZONTAL_LINE(6, 4)
        }
    },
};

Movement_Rules movement_rules_team_2[6] = {
    {
        .attack_position = {
            .x = VERTICAL_LINE(6, 2),
            .y = HORIZONTAL_LINE(2, 1)
        },
        .defend_position = {
            .x = VERTICAL_LINE(2, 1),
            .y = HORIZONTAL_LINE(2, 1)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 0),
            .right  = VERTICAL_LINE(2, 1),
            .top    = HORIZONTAL_LINE(6, 2),
            .bottom = HORIZONTAL_LINE(6, 4)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(6, 1),
            .y = HORIZONTAL_LINE(6, 2)
        },
        .defend_position = {
            .x = VERTICAL_LINE(6, 2),
            .y = HORIZONTAL_LINE(4, 1)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 0),
            .right  = VERTICAL_LINE(2, 1),
            .top    = HORIZONTAL_LINE(6, 0),
            .bottom = HORIZONTAL_LINE(6, 2)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(6, 1),
            .y = HORIZONTAL_LINE(6, 4)
        },
        .defend_position = {
            .x = VERTICAL_LINE(6, 2),
            .y = HORIZONTAL_LINE(4, 3)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 0),
            .right  = VERTICAL_LINE(2, 1),
            .top    = HORIZONTAL_LINE(6, 4),
            .bottom = HORIZONTAL_LINE(6, 6)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(2, 1),
            .y = HORIZONTAL_LINE(4, 1)
        },
        .defend_position = {
            .x = VERTICAL_LINE(4, 3),
            .y = HORIZONTAL_LINE(4, 1)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 1),
            .right  = VERTICAL_LINE(2, 2),
            .top    = HORIZONTAL_LINE(2, 0),
            .bottom = HORIZONTAL_LINE(2, 1)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(2, 1),
            .y = HORIZONTAL_LINE(4, 3)
        },
        .defend_position = {
            .x = VERTICAL_LINE(4, 3),
            .y = HORIZONTAL_LINE(4, 3)
        },
        .box = {
            .left   = VERTICAL_LINE(2, 1),
            .right  = VERTICAL_LINE(2, 2),
            .top    = HORIZONTAL_LINE(2, 1),
            .bottom = HORIZONTAL_LINE(2, 2)
        }
    },
    {
        .attack_position = {
            .x = VERTICAL_LINE(12, 11),
            .y = HORIZONTAL_LINE(2, 1)
        },
        .defend_position = {
            .x = VERTICAL_LINE(24, 23),
            .y = HORIZONTAL_LINE(2, 1)
        },
        .box = {
            .left   = VERTICAL_LINE(12, 11),
            .right  = VERTICAL_LINE(6, 6),
            .top    = HORIZONTAL_LINE(6, 2),
            .bottom = HORIZONTAL_LINE(6, 4)
        }
    },
};

//logics functions
//movement
void movement_logic_1(struct Player *self, const struct Scene *scene, Movement_Rules *movement_rules, int kit);
void movement_logic_2(struct Player *self, const struct Scene *scene, Movement_Rules *movement_rules, int kit);
//shooting
void shooting_logic_1(struct Player *self, const struct Scene *scene);
void shooting_logic_2(struct Player *self, const struct Scene *scene);
//change state
void change_state_logic_1(struct Player *self, const struct Scene *scene, struct Movement_Rules movement_rule);
void change_state_logic_2(struct Player *self, const struct Scene *scene, struct Movement_Rules movement_rule);
//utills
void shooting2selected_diraction(struct Player *self, struct Ball *ball, Vec2 direction);
void moving2selected_diraction(struct Player *self, Vec2 direction);
Vec2 find_near_teammate(struct Player *self, struct Team *team);
Vec2 find_near_next_teammate(struct Player *self, struct Team *team);
bool ball_in_box(struct Ball *ball, Box box);
bool player_in_box(struct Player *player, Box box);
bool is_opponent_near(struct Player *self, struct Team *team);
bool check_and_avoid_colliding(struct Player *self, Vec2* direction, const struct Scene *scene);
Vec2 find_goolkeeper(struct Team *team, int team_number);

//check scene state
bool is_kickoff(const struct Scene *scene);
bool is_out(const struct Scene *scene);

//check player state
int player_ball_colliding(const struct Player* p, const struct Ball* b);
int player_player_colliding(const struct Player* p1, const struct Player* p2);
bool is_ball_getting_close(struct Player *self, struct Ball *ball);

// Set to false to let the other team use their own logic (if you implement it)
// Set to true to test your logic on both teams
bool coach_both_teams = false;

/* -------------------------------------------------------------------------
 * Logic Functions
 *  TODO 1: You must implement the following functions in Phase 2.
 *        Each player in each team has its own functions.
 *        You can add new functions, but are NOT ALLOWED to remove
 *        the existing functions or change their structure.
 * ------------------------------------------------------------------------- 
 * ⚠️ STUDENT RULES FOR PHASE 2:
 * You are restricted to modifying ONLY specific variables in each function:
 *
 * 1. MOVEMENT FUNCTIONS (movement_logic_X_Y):
 * Allowed: player->velocity
 * Goal:    Determine the direction and speed of movement.
 *
 * 2. SHOOTING FUNCTIONS (shooting_logic_X_Y):
 * Allowed: ball->velocity
 * Goal:    Determine the direction and power of the kick/pass.
 *
 * 3. CHANGE STATE FUNCTIONS (change_state_logic_X_Y):
 * Allowed: player->state
 * Goal:    Switch between IDLE, MOVING, SHOOTING, or INTERCEPTING.
 *
 * NOTE: Directly modifying any other attributes will be flagged as a violation.
 * Thank you for your attention to this matter!
 * ------------------------------------------------------------------------- */

/* Team 1 movement logic */
void movement_logic_1_0(struct Player *self, struct Scene *scene) { movement_logic_1(self, scene, &movement_rules_team_1[0], 0);}
void movement_logic_1_1(struct Player *self, struct Scene *scene) { movement_logic_1(self, scene, &movement_rules_team_1[1], 1); }
void movement_logic_1_2(struct Player *self, struct Scene *scene) { movement_logic_1(self, scene, &movement_rules_team_1[2], 2); }
void movement_logic_1_3(struct Player *self, struct Scene *scene) { movement_logic_1(self, scene, &movement_rules_team_1[3], 3); }
void movement_logic_1_4(struct Player *self, struct Scene *scene) { movement_logic_1(self, scene, &movement_rules_team_1[4], 4); }
void movement_logic_1_5(struct Player *self, struct Scene *scene) { 

    struct Movement_Rules *movement_rules = &movement_rules_team_1[5];
    struct Ball *ball = scene->ball;

    Vec2 direction = {.x = 0, .y = 0};

    if (self->position.x - PLAYER_RADIUS <= LEFT_LINE){
        
        direction.x = 1;

    }else if (self->position.x + PLAYER_RADIUS >= RIGHT_LINE){
        
        direction.x = -1;

    }else if (self->position.y - PLAYER_RADIUS <= TOP_LINE){
        
        direction.y = 1;

    }else if (self->position.y + PLAYER_RADIUS >= BOTTOM_LINE){

        direction.y = -1;

    }else if (check_and_avoid_colliding(self, &direction, scene)){


    }else if (ball->possessor &&  ball->possessor->team == 1){

        direction.x = movement_rules->attack_position.x - self->position.x;
        direction.y = movement_rules->attack_position.y - self->position.y;      

    }else if (ball_in_box(ball, movement_rules->box)){

        direction.x = ball->position.x - self->position.x;
        direction.y = ball->position.y - self->position.y;

    }else if (LEFT_LINE + BALL_RADIUS < ball->position.x && ball->position.x <= CENTER_X){

        direction.x = movement_rules->defend_position.x - self->position.x;
        direction.y = ((ball->position.y - CENTER_Y) * ((movement_rules->defend_position.x - LEFT_LINE) / (ball->position.x - LEFT_LINE)) + CENTER_Y) - self->position.y;

    }else {

        direction.x = movement_rules->defend_position.x - self->position.x;
        direction.y = movement_rules->defend_position.y - self->position.y;            

    }
    
    moving2selected_diraction(self, direction);
}

/* Team 2 movement logic */
void movement_logic_2_0(struct Player *self, struct Scene *scene) { movement_logic_2(self, scene, &movement_rules_team_2[0], 0); }
void movement_logic_2_1(struct Player *self, struct Scene *scene) { movement_logic_2(self, scene, &movement_rules_team_2[1], 1); }
void movement_logic_2_2(struct Player *self, struct Scene *scene) { movement_logic_2(self, scene, &movement_rules_team_2[2], 2); }
void movement_logic_2_3(struct Player *self, struct Scene *scene) { movement_logic_2(self, scene, &movement_rules_team_2[3], 3); }
void movement_logic_2_4(struct Player *self, struct Scene *scene) { movement_logic_2(self, scene, &movement_rules_team_2[4], 4); }
void movement_logic_2_5(struct Player *self, struct Scene *scene) {

    struct Movement_Rules *movement_rules = &movement_rules_team_2[5];
    struct Ball *ball = scene->ball;

    Vec2 direction = {.x = 0, .y = 0};

    if (self->position.x - PLAYER_RADIUS <= LEFT_LINE){
        
        direction.x = 1;

    }else if (self->position.x + PLAYER_RADIUS >= RIGHT_LINE){
        
        direction.x = -1;

    }else if (self->position.y - PLAYER_RADIUS <= TOP_LINE){
        
        direction.y = 1;

    }else if (self->position.y + PLAYER_RADIUS >= BOTTOM_LINE){

        direction.y = -1;

    }else if (check_and_avoid_colliding(self, &direction, scene)){


    }else if (ball->possessor &&  ball->possessor->team == 2){

        direction.x = movement_rules->attack_position.x - self->position.x;
        direction.y = movement_rules->attack_position.y - self->position.y;      

    }else if (ball_in_box(ball, movement_rules->box)){

        direction.x = ball->position.x - self->position.x;
        direction.y = ball->position.y - self->position.y;

    }else if (RIGHT_LINE - BALL_RADIUS > ball->position.x && ball->position.x >= CENTER_X){

        direction.x = movement_rules->defend_position.x - self->position.x;
        direction.y = ((ball->position.y - CENTER_Y) * ((RIGHT_LINE - movement_rules->defend_position.x) / (RIGHT_LINE - ball->position.x)) + CENTER_Y) - self->position.y;

    }else {

        direction.x = movement_rules->defend_position.x - self->position.x;
        direction.y = movement_rules->defend_position.y - self->position.y;            

    }
    
    moving2selected_diraction(self, direction);
}

/* Team 1 shooting logic */
void shooting_logic_1_0(struct Player *self, struct Scene *scene) { shooting_logic_1(self, scene); }
void shooting_logic_1_1(struct Player *self, struct Scene *scene) { shooting_logic_1(self, scene); }
void shooting_logic_1_2(struct Player *self, struct Scene *scene) { shooting_logic_1(self, scene); }
void shooting_logic_1_3(struct Player *self, struct Scene *scene) { shooting_logic_1(self, scene); }
void shooting_logic_1_4(struct Player *self, struct Scene *scene) { shooting_logic_1(self, scene); }
void shooting_logic_1_5(struct Player *self, struct Scene *scene) { shooting_logic_1(self, scene); }

/* Team 2 shooting logic */
void shooting_logic_2_0(struct Player *self, struct Scene *scene) { shooting_logic_2(self, scene); }
void shooting_logic_2_1(struct Player *self, struct Scene *scene) { shooting_logic_2(self, scene); }
void shooting_logic_2_2(struct Player *self, struct Scene *scene) { shooting_logic_2(self, scene); }
void shooting_logic_2_3(struct Player *self, struct Scene *scene) { shooting_logic_2(self, scene); }
void shooting_logic_2_4(struct Player *self, struct Scene *scene) { shooting_logic_2(self, scene); }
void shooting_logic_2_5(struct Player *self, struct Scene *scene) { shooting_logic_2(self, scene); }

/* Team 1 change_state logic */
void change_state_logic_1_0(struct Player *self, struct Scene *scene) { change_state_logic_1(self, scene, movement_rules_team_1[0]); }
void change_state_logic_1_1(struct Player *self, struct Scene *scene) { change_state_logic_1(self, scene, movement_rules_team_1[1]); }
void change_state_logic_1_2(struct Player *self, struct Scene *scene) { change_state_logic_1(self, scene, movement_rules_team_1[2]); }
void change_state_logic_1_3(struct Player *self, struct Scene *scene) { change_state_logic_1(self, scene, movement_rules_team_1[3]); }
void change_state_logic_1_4(struct Player *self, struct Scene *scene) { change_state_logic_1(self, scene, movement_rules_team_1[4]); }
void change_state_logic_1_5(struct Player *self, struct Scene *scene) { change_state_logic_1(self, scene, movement_rules_team_1[5]); }


/* Team 2 change_state logic */
void change_state_logic_2_0(struct Player *self, struct Scene *scene) { change_state_logic_2(self, scene, movement_rules_team_2[0]); }
void change_state_logic_2_1(struct Player *self, struct Scene *scene) { change_state_logic_2(self, scene, movement_rules_team_2[1]); }
void change_state_logic_2_2(struct Player *self, struct Scene *scene) { change_state_logic_2(self, scene, movement_rules_team_2[2]); }
void change_state_logic_2_3(struct Player *self, struct Scene *scene) { change_state_logic_2(self, scene, movement_rules_team_2[3]); }
void change_state_logic_2_4(struct Player *self, struct Scene *scene) { change_state_logic_2(self, scene, movement_rules_team_2[4]); }
void change_state_logic_2_5(struct Player *self, struct Scene *scene) { change_state_logic_2(self, scene, movement_rules_team_2[5]); }

/* -------------------------------------------------------------------------
 * Lookup tables for factory
 * ------------------------------------------------------------------------- */
static PlayerLogicFn team1_movement[6] = {
    movement_logic_1_0, movement_logic_1_1, movement_logic_1_2,
    movement_logic_1_3, movement_logic_1_4, movement_logic_1_5
};

static PlayerLogicFn team2_movement[6] = {
    movement_logic_2_0, movement_logic_2_1, movement_logic_2_2,
    movement_logic_2_3, movement_logic_2_4, movement_logic_2_5
};

static PlayerLogicFn team1_shooting[6] = {
    shooting_logic_1_0, shooting_logic_1_1, shooting_logic_1_2,
    shooting_logic_1_3, shooting_logic_1_4, shooting_logic_1_5
};

static PlayerLogicFn team2_shooting[6] = {
    shooting_logic_2_0, shooting_logic_2_1, shooting_logic_2_2,
    shooting_logic_2_3, shooting_logic_2_4, shooting_logic_2_5
};

static PlayerLogicFn team1_change_state[6] = {
    change_state_logic_1_0, change_state_logic_1_1, change_state_logic_1_2,
    change_state_logic_1_3, change_state_logic_1_4, change_state_logic_1_5
};

static PlayerLogicFn team2_change_state[6] = {
    change_state_logic_2_0, change_state_logic_2_1, change_state_logic_2_2,
    change_state_logic_2_3, change_state_logic_2_4, change_state_logic_2_5
};

/* -------------------------------------------------------------------------
 * Factory functions
 * ------------------------------------------------------------------------- */
PlayerLogicFn get_movement_logic(int team, int kit) {
    if (coach_both_teams) return team1_movement[kit];
    return (team == 1) ? team1_movement[kit] : team2_movement[kit];
}

PlayerLogicFn get_shooting_logic(int team, int kit) {
    if (coach_both_teams) return team1_shooting[kit];
    return (team == 1) ? team1_shooting[kit] : team2_shooting[kit];
}

PlayerLogicFn get_change_state_logic(int team, int kit) {
    if (coach_both_teams) return team1_change_state[kit];
    return (team == 1) ? team1_change_state[kit] : team2_change_state[kit];
}

/* -------------------------------------------------------------------------
 * TALENTS
 *  TODO 2: Replace these default values with your desired skill points.
 * ------------------------------------------------------------------------- */
/* Team 1 */
static struct Talents team1_talents[6] = {
    {4, 4, 6, 6},
    {3, 5, 4, 8},
    {3, 5, 4, 8},
    {10, 4, 3, 3},
    {10, 4, 3, 3},
    {10, 4, 2, 4},
};

/* Team 2 */
static struct Talents team2_talents[6] = {
    {1, 8, 2, 9},
    {1, 9, 2, 8},
    {1, 9, 2, 8},
    {7, 5, 4, 4},
    {7, 5, 4, 4},
    {10, 4, 2, 4},
};

struct Talents get_talents(int team, int kit) {
    if (coach_both_teams) return team1_talents[kit];
    return (team == 1) ? team1_talents[kit] : team2_talents[kit];
}


/* -------------------------------------------------------------------------
 * Positioning
 *  TODO 3: Decide players positions at kick-off.
 *        Players must stay on their half, outside the center circle.
 *        Keep in mind that the kick-off team's first player will automatically
 *             be placed at the center of the pitch.
 * ------------------------------------------------------------------------- */
/* Team 1 */
static struct Vec2 team1_positions[6] = {
    {VERTICAL_LINE(6, 2), HORIZONTAL_LINE(2, 1)},
    {VERTICAL_LINE(12, 4), HORIZONTAL_LINE(12, 5)},
    {VERTICAL_LINE(12, 4), HORIZONTAL_LINE(12, 7)},
    {VERTICAL_LINE(4, 1), HORIZONTAL_LINE(4, 1)},
    {VERTICAL_LINE(4, 1), HORIZONTAL_LINE(4, 3)},
    {VERTICAL_LINE(12, 1), HORIZONTAL_LINE(2, 1)},
};

/* Team 2 */
static struct Vec2 team2_positions[6] = {
    {VERTICAL_LINE(6, 4), HORIZONTAL_LINE(2, 1)},
    {VERTICAL_LINE(12, 8), HORIZONTAL_LINE(12, 5)},
    {VERTICAL_LINE(12, 8), HORIZONTAL_LINE(12, 7)},
    {VERTICAL_LINE(4, 3), HORIZONTAL_LINE(4, 1)},
    {VERTICAL_LINE(4, 3), HORIZONTAL_LINE(4, 3)},
    {VERTICAL_LINE(12, 11), HORIZONTAL_LINE(2, 1)},
};

struct Vec2 get_positions(int team, int kit) {
    return (team == 1) ? team1_positions[kit] : team2_positions[kit];
}

//logics functions

//movement
void movement_logic_1(struct Player *self, const struct Scene *scene, Movement_Rules *movement_rules, int kit){

    struct Ball *ball = scene->ball;

    Vec2 direction = {.x = 0, .y = 0};

    if (self->position.x - PLAYER_RADIUS <= LEFT_LINE){
        
        direction.x = 1;

    }else if (self->position.x + PLAYER_RADIUS >= RIGHT_LINE){
        
        direction.x = -1;

    }else if (self->position.y - PLAYER_RADIUS <= TOP_LINE){
        
        direction.y = 1;

    }else if (self->position.y + PLAYER_RADIUS >= BOTTOM_LINE){

        direction.y = -1;

    }else if (check_and_avoid_colliding(self, &direction, scene)){


    }else if (ball->possessor == self && self->position.x >= VERTICAL_LINE(6,4)){

        direction.x = RIGHT_LINE - self->position.x;
        direction.y = movement_rules->attack_position.y - self->position.y;      

    }else if (ball->possessor &&  ball->possessor->team == 1){

        direction.x = movement_rules->attack_position.x - self->position.x;
        direction.y = movement_rules->attack_position.y - self->position.y;      

    }else if (ball_in_box(ball, movement_rules->box)){

        if ((kit == 3 || kit == 4) && (ball->possessor && ball->possessor->team == 2) && (movement_rules->defend_position.x <= ball->position.x && ball->position.x <= CENTER_X)){

            direction.x = movement_rules->defend_position.x - self->position.x;
            direction.y = ((ball->position.y - CENTER_Y) * ((movement_rules->defend_position.x - LEFT_LINE) / (ball->position.x - LEFT_LINE)) + CENTER_Y) - self->position.y;

        }else {
        
            direction.x = ball->position.x - self->position.x;
            direction.y = ball->position.y - self->position.y;

        }

    }else if (!ball->possessor &&  ball->last_team == 1){

        direction.x = movement_rules->attack_position.x - self->position.x;
        direction.y = movement_rules->attack_position.y - self->position.y;      

    }else if ((kit == 3 || kit == 4) && (movement_rules->defend_position.x <= ball->position.x && ball->position.x <= CENTER_X)){

        direction.x = movement_rules->defend_position.x - self->position.x;
        direction.y = ((ball->position.y - CENTER_Y) * ((movement_rules->defend_position.x - LEFT_LINE) / (ball->position.x - LEFT_LINE)) + CENTER_Y) - self->position.y;

    }else {

        direction.x = movement_rules->defend_position.x - self->position.x;
        direction.y = movement_rules->defend_position.y - self->position.y;            

    }
    
    moving2selected_diraction(self, direction);

}

void movement_logic_2(struct Player *self, const struct Scene *scene, Movement_Rules *movement_rules, int kit){

    struct Ball *ball = scene->ball;

    Vec2 direction = {.x = 0, .y = 0};

    if (self->position.x - PLAYER_RADIUS <= LEFT_LINE){
        
        direction.x = 1;

    }else if (self->position.x + PLAYER_RADIUS >= RIGHT_LINE){
        
        direction.x = -1;

    }else if (self->position.y - PLAYER_RADIUS <= TOP_LINE){
        
        direction.y = 1;

    }else if (self->position.y + PLAYER_RADIUS >= BOTTOM_LINE){

        direction.y = -1;

    }else if (check_and_avoid_colliding(self, &direction, scene)){


    }else if (ball->possessor == self && self->position.x <= VERTICAL_LINE(6,2)){

        direction.x = LEFT_LINE - self->position.x;
        direction.y = movement_rules->attack_position.y - self->position.y;      

    }else if(ball->possessor &&  ball->possessor->team == 2){

        direction.x = movement_rules->attack_position.x - self->position.x;
        direction.y = movement_rules->attack_position.y - self->position.y;      

    }else if(ball_in_box(ball, movement_rules->box)){

        if ((kit == 3 || kit == 4) && (ball->possessor &&  ball->possessor->team == 1) && (movement_rules->defend_position.x >= ball->position.x && ball->position.x >= CENTER_X)){

            direction.x = movement_rules->defend_position.x - self->position.x;
            direction.y = ((ball->position.y - CENTER_Y) * ((RIGHT_LINE - movement_rules->defend_position.x) / (RIGHT_LINE - ball->position.x)) + CENTER_Y) - self->position.y;


        }else {
         
            direction.x = ball->position.x - self->position.x;
            direction.y = ball->position.y - self->position.y;

        }

    }else if(!ball->possessor &&  ball->last_team == 2){

        direction.x = movement_rules->attack_position.x - self->position.x;
        direction.y = movement_rules->attack_position.y - self->position.y;      

    }else {

        direction.x = movement_rules->defend_position.x - self->position.x;
        direction.y = movement_rules->defend_position.y - self->position.y;            

    }

    moving2selected_diraction(self, direction);

}

//shooting
void shooting_logic_1(struct Player *self, const struct Scene *scene){

    struct Ball* ball = scene->ball;
    float max_ball_velocity = MAX_BALL_VELOCITY * (self->talents.shooting  / (float)MAX_TALENT_PER_SKILL);

    Vec2 direction;

    Vec2 goal_distance_vec = {
        .x = RIGHT_LINE - self->position.x,
        .y = CENTER_Y - self->position.y
    };

    Vec2 goolkeeper_position = find_goolkeeper(scene->second_team, 2);

    int goalkeeper_player_one_side = ((CENTER_Y < self->position.y) + (CENTER_Y < goolkeeper_position.y)) % 2 == 0;

    float goal_distance = lengthVec2(&goal_distance_vec);
    

    if (is_kickoff(scene) || is_out(scene)){

        Vec2 teammate = find_near_teammate(self, scene->first_team);

        direction.x = teammate.x - ball->position.x;
        direction.y = teammate.y - ball->position.y;
        
    }else if(goal_distance > SHOOTING_REDUCE || goalkeeper_player_one_side){

        Vec2 teammate = find_near_next_teammate(self, scene->first_team);

        direction.x = teammate.x - ball->position.x;
        direction.y = teammate.y - ball->position.y;

    }else if (self->position.y < CENTER_Y){

        direction.x = RIGHT_LINE - ball->position.x;
        direction.y =  CENTER_Y -  0.8*GOAL_HEIGHT/2 - ball->position.y;
        
    }else {

        direction.x = RIGHT_LINE - ball->position.x;
        direction.y =  CENTER_Y +  0.8*GOAL_HEIGHT/2 - ball->position.y;        

    }

    shooting2selected_diraction(self, ball, direction);
                   
}

void shooting_logic_2(struct Player *self, const struct Scene *scene){

    struct Ball* ball = scene->ball;
    float max_ball_velocity = MAX_BALL_VELOCITY * (self->talents.shooting  / (float)MAX_TALENT_PER_SKILL);

    Vec2 direction;

    Vec2 goal_distance_vec = {
        .x = LEFT_LINE - self->position.x,
        .y = CENTER_Y - self->position.y
    };

    Vec2 goolkeeper_position = find_goolkeeper(scene->first_team, 1);

    int goalkeeper_player_one_side = ((CENTER_Y < self->position.y) + (CENTER_Y < goolkeeper_position.y)) % 2 == 0; 

    float goal_distance = lengthVec2(&goal_distance_vec);
    
    if (is_kickoff(scene) || is_out(scene)){

        Vec2 teammate = find_near_teammate(self, scene->second_team);

        direction.x = teammate.x - ball->position.x;
        direction.y = teammate.y - ball->position.y;
        
    }else if(goal_distance > SHOOTING_REDUCE || goalkeeper_player_one_side){

        Vec2 teammate = find_near_next_teammate(self, scene->second_team);

        direction.x = teammate.x - ball->position.x;
        direction.y = teammate.y - ball->position.y;

    }else if(self->position.y < CENTER_Y){

        direction.x = LEFT_LINE - ball->position.x;
        direction.y =  CENTER_Y - 0.8*GOAL_HEIGHT/2 - ball->position.y;
    
    }else {

        direction.x = LEFT_LINE - ball->position.x;
        direction.y =  CENTER_Y + 0.8*GOAL_HEIGHT/2 - ball->position.y;

    }
    
    shooting2selected_diraction(self, ball, direction);

}

//change state
void change_state_logic_1(struct Player *self, const struct Scene *scene, struct Movement_Rules movement_rule){

    struct Ball* ball = scene->ball;
    
    Vec2 goal_distance_vec = {
        .x = RIGHT_LINE - self->position.x,
        .y = CENTER_Y - self->position.y
    };

    Vec2 goolkeeper_position = find_goolkeeper(scene->second_team, 2);

    int goalkeeper_player_one_side = ((CENTER_Y < self->position.y) + (CENTER_Y < goolkeeper_position.y)) % 2 == 0;
    int shoot2goal = !goalkeeper_player_one_side && lengthVec2(&goal_distance_vec) < SHOOTING_REDUCE; 

    if (self == ball->possessor){

        if (is_opponent_near(self, scene->second_team) || movement_rule.box.right <= self->position.x || shoot2goal){

            self->state = SHOOTING;
            
        }else{

            self->state = MOVING;

        }
        
    }else {

        if (player_ball_colliding(self, ball) && (is_ball_getting_close(self, ball) || scene->ball->possessor)){
            
            self->state = INTERCEPTING; 

        }else{

            self->state = MOVING;

        }

    }

}

void change_state_logic_2(struct Player *self, const struct Scene *scene, struct Movement_Rules movement_rule){ 

    struct Ball* ball = scene->ball;
    
    Vec2 goal_distance_vec = {
        .x = LEFT_LINE - self->position.x,
        .y = CENTER_Y - self->position.y
    };

    Vec2 goolkeeper_position = find_goolkeeper(scene->first_team, 1);

    int goalkeeper_player_one_side = ((CENTER_Y < self->position.y) + (CENTER_Y < goolkeeper_position.y)) % 2 == 0;
    int shoot2goal = !goalkeeper_player_one_side && lengthVec2(&goal_distance_vec) < SHOOTING_REDUCE; 

    if (self == ball->possessor){

        if (is_opponent_near(self, scene->first_team) || movement_rule.box.left >= self->position.x || shoot2goal){

            self->state = SHOOTING;
            
        }else{

            self->state = MOVING;

        }
        
    }else {

        if (player_ball_colliding(self, ball) && (is_ball_getting_close(self, ball) || scene->ball->possessor)){
            
            self->state = INTERCEPTING;

        }else{

            self->state = MOVING;

        }

    }

}

//utills
void shooting2selected_diraction(struct Player *self, struct Ball *ball, Vec2 direction){

    float max_ball_velocity = MAX_BALL_VELOCITY * (self->talents.shooting  / (float)MAX_TALENT_PER_SKILL);

    float delta_x_diraction = 2 * (direction.x > 0) - 1;
    float delta_y_diraction = 2 * (direction.y > 0) - 1;

    if (direction.x == 0.0f){

        ball->velocity.y = max_ball_velocity * delta_y_diraction;
        return;
    
    }
    
    if (direction.y == 0.0f){

        ball->velocity.x = max_ball_velocity * delta_x_diraction;
        return;

    }
    

    float tan = direction.y / direction.x;
    float cot = direction.x / direction.y;

    if (-1 < tan && tan < 1){
        
        ball->velocity.x = max_ball_velocity * delta_x_diraction;
        ball->velocity.y = ball->velocity.x * tan; 

    }else{

        ball->velocity.y = max_ball_velocity * delta_y_diraction;
        ball->velocity.x = ball->velocity.y * cot;         

    }

}

void moving2selected_diraction(struct Player *self, Vec2 direction){

    float max_player_velocity = MAX_PLAYER_VELOCITY * (self->talents.agility / (float)MAX_TALENT_PER_SKILL);

    float delta_x_diraction = 2 * (direction.x > 0) - 1;
    float delta_y_diraction = 2 * (direction.y > 0) - 1;

    if (direction.x == 0.0f){

        self->velocity.y = max_player_velocity * delta_y_diraction;
        return;
    
    }
    
    if (direction.y == 0.0f){

        self->velocity.x = max_player_velocity * delta_x_diraction;
        return;

    }


    float tan = direction.y / direction.x;
    float cot = direction.x / direction.y;

    if (-1 < tan && tan < 1){
        
        self->velocity.x = max_player_velocity * delta_x_diraction;
        self->velocity.y = self->velocity.x * tan; 

    }else{

        self->velocity.y = max_player_velocity * delta_y_diraction; 
        self->velocity.x = self->velocity.y * cot;
                
    }

}

Vec2 find_near_teammate(struct Player *self, struct Team *team){

    struct Player* nearest_player;
    float min_distance;

    bool first_time = 1;

    for (int i = 0; i < PLAYER_COUNT; i++) {
        struct Player* p = team->players[i];

        Vec2 distance_vec;
        distance_vec.x = p->position.x - self->position.x;
        distance_vec.y = p->position.y - self->position.y;
        
        float distance = lengthVec2(&distance_vec);

        if ((first_time || min_distance > distance) && self != p && distance > 4 * PLAYER_RADIUS){
            
            min_distance = distance;
            nearest_player = p;

            if (first_time){
                
                first_time = 0;

            }

        }

    }


    return nearest_player->position;
    
}

Vec2 find_near_next_teammate(struct Player *self, struct Team *team){

    struct Player* nearest_player;
    float min_distance;

    bool first_time = 1;

    for (int i = 0; i < PLAYER_COUNT; i++) {
        struct Player* p = team->players[i];

        Vec2 distance_vec;
        distance_vec.x = p->position.x - self->position.x;
        distance_vec.y = p->position.y - self->position.y;
        
        float distance = lengthVec2(&distance_vec);

        if ((first_time || min_distance > distance) && self != p  && distance > 4 * PLAYER_RADIUS && 0 < distance_vec.x * ((self->team%2)*2-1) ){
            
            min_distance = distance;
            nearest_player = p;

            if (first_time){
                
                first_time = 0;

            }

        }

    }

    if (first_time == 1){

        return find_near_teammate(self, team);

    }else {
    
        return nearest_player->position;
    
    }
    
}

bool ball_in_box(struct Ball *ball, Box box){

    bool x_in_box = box.left <= ball->position.x + BALL_RADIUS && ball->position.x - BALL_RADIUS <= box.right;
    bool y_in_box = box.top <= ball->position.y + BALL_RADIUS && ball->position.y - BALL_RADIUS <= box.bottom;

    if (x_in_box && y_in_box)
        return true;
    
    return false;
}

bool player_in_box(struct Player *player, Box box){

    bool x_in_box = box.left <= player->position.x && player->position.x <= box.right;
    bool y_in_box = box.top <= player->position.y && player->position.y <= box.bottom;

    if (x_in_box && y_in_box)
        return true;
    
    return false;
}

bool is_opponent_near(struct Player *self, struct Team *team){

    Box box;

    if (self->team == 1){
        
        box.left = self->position.x - 2 * PLAYER_RADIUS;
        box.right = self->position.x + 5 * PLAYER_RADIUS;

    }else{

        box.left = self->position.x - 5 * PLAYER_RADIUS;
        box.right = self->position.x + 2 * PLAYER_RADIUS;

    }

    box.bottom = self->position.y + 3.5 * PLAYER_RADIUS;
    box.top = self->position.y - 3.5 * PLAYER_RADIUS;

    for (int i = 0; i < 6; i++){
        
        struct Player* p = team->players[i];

        if (player_in_box(p, box))
            return true;
        
    }

    return false;

}

bool check_and_avoid_colliding(struct Player *self, Vec2* direction, const struct Scene *scene){
    
    for (int i = 0; i < PLAYER_COUNT; i++) {
        struct Player* p1 = scene->first_team->players[i];
        struct Player* p2 = scene->second_team->players[i];

        if (self != p1 && player_player_colliding(self, p1)){
            
            direction->x =  -(p1->position.x - self->position.x); 
            direction->y =  -(p1->position.y - self->position.y);             

            return true;
        }

        if (self != p2 && player_player_colliding(self, p2)){

            direction->x =  -(p2->position.x - self->position.x); 
            direction->y =  -(p2->position.y - self->position.y); 

            return true;
        }
    }
    
    return false;
}

Vec2 find_goolkeeper(struct Team *team, int team_number){
    
    Vec2 goolkeeper_position;

    if (team_number == 1){

        float min_distance;

        bool first_time = 1;

        for (int i = 0; i < PLAYER_COUNT; i++) {
            struct Player* p = team->players[i];

            Vec2 distance_vec;

            distance_vec.x = p->position.x - LEFT_LINE;
            distance_vec.y = p->position.y - CENTER_Y;

            float distance = lengthVec2(&distance_vec);

            if (first_time || min_distance > distance){
                
                min_distance = distance;
                goolkeeper_position = p->position;

                if (first_time){
                    
                    first_time = 0;

                }

            }

        }

    }else {

        float min_distance;

        bool first_time = 1;

        for (int i = 0; i < PLAYER_COUNT; i++) {
            struct Player* p = team->players[i];

            Vec2 distance_vec;

            distance_vec.x = RIGHT_LINE - p->position.x;
            distance_vec.y = p->position.y - CENTER_Y;

            float distance = lengthVec2(&distance_vec);

            if (first_time || min_distance > distance){
                
                min_distance = distance;
                goolkeeper_position = p->position;

                if (first_time){
                    
                    first_time = 0;

                }

            }

        }


    }
    

    return goolkeeper_position;

}

//check scene state
bool is_kickoff(const Scene *scene){

    struct Ball* ball = scene->ball;

    if (!(ball->velocity.x == 0.0f && ball->velocity.y == 0.0f && ball->position.x == CENTER_X && ball->position.y == CENTER_Y))
        return false;
    
    for (int i = 0; i < PLAYER_COUNT; i++) {
        struct Player* p1 = scene->first_team->players[i];
        struct Player* p2 = scene->second_team->players[i];

        if (!(p1->velocity.x == 0.0f && p1->velocity.y == 0.0f && p2->velocity.x == 0.0f && p2->velocity.y == 0.0f)){
            return false;
        }
    }
    
    return true;
}

bool is_out(const Scene *scene){

    struct Ball* ball = scene->ball;

    if (!(ball->velocity.x == 0.0f && ball->velocity.y == 0.0f))
        return false;
    
    for (int i = 0; i < PLAYER_COUNT; i++) {
        struct Player* p1 = scene->first_team->players[i];
        struct Player* p2 = scene->second_team->players[i];

        if (!(p1->velocity.x == 0.0f && p1->velocity.y == 0.0f && p2->velocity.x == 0.0f && p2->velocity.y == 0.0f))
            return false;
        
    }

    bool on_border = ball->position.x == RIGHT_LINE || ball->position.y == TOP_LINE || ball->position.x == LEFT_LINE || ball->position.y == BOTTOM_LINE ;
    bool next2left_goal = ball->position.x == LEFT_LINE + PITCH_MARGIN && ball->position.y == CENTER_Y;
    bool next2right_goal = ball->position.x == RIGHT_LINE - PITCH_MARGIN && ball->position.y == CENTER_Y;
    
    if (!(on_border || next2left_goal || next2right_goal ))
        return false;

    return true;
}

//check player state
int player_ball_colliding(const struct Player* p, const struct Ball* b) {
    // Standard Circle-to-Circle collision math: (dist^2 <= combined_radius^2)
    float dx = p->position.x - b->position.x;
    float dy = p->position.y - b->position.y;
    float dist_sq = dx * dx + dy * dy;
    float radius_sum = p->radius + b->radius;
    return dist_sq <= radius_sum * radius_sum;
}

int player_player_colliding(const struct Player* p1, const struct Player* p2) {
    // Standard Circle-to-Circle collision math: (dist^2 <= combined_radius^2)
    float dx = p1->position.x - p2->position.x;
    float dy = p1->position.y - p2->position.y;
    float dist_sq = dx * dx + dy * dy;
    float radius_sum = p1->radius + p2->radius;
    return dist_sq <= radius_sum * radius_sum;
}

bool is_ball_getting_close(struct Player *self, struct Ball *ball){

    Vec2 delta_r;
    vec2_sub(&delta_r, &(ball->position), &(self->position));

    bool getting_close = dotProduct(&(ball->velocity), &delta_r) <= 0;
    return getting_close;
}
