/*
** EPITECH PROJECT, 2022
** test_map
** File description:
** scene_event.c
*/

#include "project.h"

void inventory_event(project_t *project, sfEvent event)
{
    if (project->inventory->is_active && event.type == sfEvtMouseButtonPressed
    && event.mouseButton.button == sfMouseLeft)
        select_box(project, (sfVector2f) {event.mouseButton.x,
        event.mouseButton.y});
    if (project->inventory->is_active && event.type == sfEvtJoystickButtonPressed
    && (event.joystickButton.button == 1 || event.joystickButton.button == 4))
        select_box(project, (sfVector2f) {project->mouse->mouse_pos.x,
        project->mouse->mouse_pos.y});
    if (project->inventory->is_active && event.type == sfEvtMouseButtonReleased
    && event.mouseButton.button == sfMouseLeft && project->inventory->state ==
    PRESSED)
        unselect_box(project, (sfVector2f) {event.mouseButton.x,
        event.mouseButton.y});
    if (project->inventory->is_active && event.type == sfEvtJoystickButtonReleased
    && (event.joystickButton.button == 1 || event.joystickButton.button == 4) && project->inventory->state ==
    PRESSED)
        unselect_box(project, (sfVector2f) {project->mouse->mouse_pos.x,
        project->mouse->mouse_pos.y});
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyLShift)
        project->inventory->shift_pressed = true;
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyLShift)
        project->inventory->shift_pressed = false;
}

void scene_event_bis(project_t *project, sfEvent event)
{
    if (event.type == sfEvtKeyPressed && (event.key.code == sfKeySpace ||
    event.key.code == sfKeyE) &&
    !project->inventory->is_active)
        check_all_pnj_dialogue(project);
    if (event.type == sfEvtJoystickButtonPressed && (event.joystickButton.button == 1 || event.joystickButton.button == 4) &&
    !project->inventory->is_active)
        check_all_pnj_dialogue(project);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyTab &&
    !project->actual_dial->is_displayed) {
        play_sound(project, "assets/music/inventory.ogg");
        switch_state_inventory(project, project->inventory);
    }
    if (event.type == sfEvtJoystickButtonPressed && event.joystickButton.button == 8 &&
    !project->actual_dial->is_displayed) {
        play_sound(project, "assets/music/inventory.ogg");
        switch_state_inventory(project, project->inventory);
    }
}

void scene_event(project_t *project)
{
    sfEvent event;

    set_all_pnj_dialogues(project);
    while (sfRenderWindow_pollEvent(project->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(project->window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape) {
            project->status = PAUSE_MENU;
            sfRenderWindow_setView(project->window,
            project->pause_menu->camera);
        }
        if (event.type == sfEvtJoystickButtonPressed && event.joystickButton.button == 9) {
            project->status = PAUSE_MENU;
            sfRenderWindow_setView(project->window,
            project->pause_menu->camera);
        }
        scene_event_bis(project, event);
        inventory_event(project, event);
        quest_event(project, event);
        if (event.type == sfEvtJoystickMoved) {
            if (event.joystickMove.position < 0.001 && event.joystickMove.position > -0.001) {
                project->mouse->is_moving = false;
            } else {
                project->mouse->is_moving = true;
                project->mouse->joystick_event = event.joystickMove;
            }
        }
    }
    if (project->mouse->is_moving == true && project->inventory->is_active) {
        if (project->mouse->joystick_event.axis == sfJoystickX) {
            if (project->mouse->joystick_event.position > 50) {
                project->mouse->mouse_pos.y -= 2;
            }
            if (project->mouse->joystick_event.position < -50) {
                project->mouse->mouse_pos.y += 2;
            }
        }
        if (project->mouse->joystick_event.axis == sfJoystickY) {
            if (project->mouse->joystick_event.position > 50) {
                project->mouse->mouse_pos.x += 2;
            }
            if (project->mouse->joystick_event.position < -50) {
                project->mouse->mouse_pos.x -= 2;
            }
        }
    }
}
