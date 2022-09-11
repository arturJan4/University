import sys
import math
from collections import namedtuple
import random

Entity = namedtuple('Entity', [
    'id', 'type', 'x', 'y', 'shield_life', 'is_controlled', 'health', 'vx', 'vy', 'near_base', 'threat_for'
])

TYPE_MONSTER = 0
TYPE_MY_HERO = 1
TYPE_OP_HERO = 2

# base_x,base_y: The corner of the map representing your base
base_x, base_y = [int(i) for i in input().split()]
base_opp_x, base_opp_y = [17630 - base_x, 9000 - base_y]
heroes_per_player = int(input())
started_top_left = (base_x == 0)


# distance between two points
def distance(x, y, x1, y2):
    return math.sqrt(math.pow(x - x1, 2) + math.pow(y - y2, 2))


# distance between two entities
def distance_e(entity1, entity2):
    return math.sqrt(math.pow(entity1.x - entity2.x, 2) + math.pow(entity1.y - entity2.y, 2))


def distance_to_own_base(monster):
    return distance(monster.x, monster.y, base_x, base_y)


def distance_to_enemy_base(monster):
    return distance(monster.x, monster.y, base_opp_x, base_opp_y)


# check if hero1 is closer than hero2 to the monster
def is_closer(hero1, hero2, monster):
    if distance_e(hero1, monster) <= distance_e(hero2, monster):
        return True
    return False


# check if monster will attack your base -> use threatLevel
def will_monster_hit(monster):
    return monster.threat_for == 1


# check if monster will attack enemy base -> use threatLevel
def will_monster_hit_enemy(monster):
    return monster.threat_for == 2


def is_monster_dead(monster, monsters):
    for m in monsters:
        if monster.id == m.id:
            return False
    return True


# in how many turns will the monster attack base in the worst case scenario
def calc_turn_attack_min(monster, attackers):
    # TODO: now it rounds down, should it?
    min_turns = 1000, ""
    monster_x, monster_y = monster.x, monster.y
    # walks straight in
    if will_monster_hit(monster):
        dist = distance_to_own_base(monster) - 300
        min_turns = dist / 400, "straight"

    # will be controlled by opponent
    # TODO: only estimate
    for hero in attackers:
        hero_x, hero_y = hero.x, hero.y
        monster_x, monster_y = monster.x, monster.y
        # simulate following
        turns = 0
        closer = 0
        while distance(monster_x, monster_y, hero_x, hero_y) - closer > 2200:
            turns += 1
            monster_x += monster.vx
            monster_y += monster.vy

            closer += 800  # more than half of 800

        turns += 1  # cast control
        # TODO: +213 because of < 300 constraint on damage
        dist = distance(monster_x, monster_y, base_x + 213, base_y + 213)
        turns += dist / 400
        if turns < min_turns[0]:
            min_turns = turns, "control"

    # will be pushed by opponent
    # TODO: only estimate

    for hero in attackers:
        hero_x, hero_y = hero.x, hero.y
        monster_x, monster_y = monster.x, monster.y
        # simulate following
        turns = 0
        closer = 0
        while distance(monster_x, monster_y, hero_x, hero_y) - closer > 1280:
            turns += 1
            monster_x += monster.vx
            monster_y += monster.vy

            closer += 800  # more than half of 800

        print(
            f"min-dist turns, before push {turns}, monster: {monster.id, monster_x, monster_y, monster.vx, monster.vy}",
            file=sys.stderr, flush=True)

        # TODO: estimated 45 degrees
        if monster_x < 213:
            monster_x = 0
        if monster_y < 213:
            monster_y = 0
        if monster_x > 17630 - 213:
            monster_x = 17630
        if monster_y > 9000 - 213:
            monster_y = 9000

        turns += 1  # cast push

        dist = distance(monster_x, monster_y, base_x, base_y) - 2200

        if dist >= 400:
            turns += dist / 400

        if turns < min_turns[0]:
            min_turns = turns, "push"

    print(f"min-dist {min_turns}, monster: {monster.id}", file=sys.stderr, flush=True)

    return min_turns


# based on turns on attack, and defenders/attackers close
def calc_danger(monster, monsters, attackers):
    pass


# default heroes positions (2 defenders, 1 attacker)
default_pos_left = [(7300, 2300), (3500, 6800), (13600, 5000)]
default_pos_right = [(17630 - x, 9000 - y) for (x, y) in default_pos_left]


# current monster position is in player's radius
def in_player_radius(player_x, player_y, monster_x, monster_y):
    if distance(player_x, player_y, monster_x, monster_y) <= 800:
        return True
    return False


# will monster be in range in next move
def in_monster_range(player_x, player_y, monsters, range_for):
    for monster in monsters:
        monster = monster_pos_next_turn(monster)
        if distance(player_x, player_y, monster[0], monster[1]) < range_for:
            return True
    return False


# return i-th hero to his default position
def return_to_position(i, monsters):
    new_x, new_y = default_pos_right[i][0], default_pos_right[i][1]
    if started_top_left:
        new_x, new_y = default_pos_left[i][0], default_pos_left[i][1]

    # if there is monster nearby -> farm instead of going to default
    for monster in monsters:
        monster = monster_pos_next_turn(monster)
        if in_player_radius(new_x, new_y, monster[0], monster[1]):
            new_x, new_y = monster[0], monster[1]
            print(f"MOVE {new_x} {new_y} return-farm")
            return

    print(f"MOVE {new_x} {new_y} return")
    return


# monsters that defenders are attacking
is_attacking = [None, None]


# coordinates of monster in the next turn
def monster_pos_next_turn(monster):
    return (monster.x + monster.vx, monster.y + monster.vy)


# attacker scanning the perimeter (up and down)
reached_base_att = False
endpoints = [(15700, 4300), (12520, 7600)]  # if top left is our base
endpoints_r = [(17630 - x, 9000 - y) for (x, y) in endpoints]
move_up_att = True


# given new position check if it will attack attacking monsters
def random_non_opponent(pos_x, pos_y, monsters):
    is_wrong = True
    ITER = 0
    new_x, new_y = pos_x, pos_y

    while is_wrong:
        is_wrong = False

        if ITER > 100:
            print(f"gave up searching randomly for next move", file=sys.stderr, flush=True)
            new_x, new_y = pos_x, pos_y
            is_wrong = False
            break
        ITER += 1

        for monster in monsters:
            if not will_monster_hit_enemy(monster):
                continue

            monster = monster_pos_next_turn(monster)
            if distance(new_x, new_y, monster[0], monster[1]) <= 800:
                new_x += random.randint(-200, 200)
                new_y += random.randint(-200, 200)
                is_wrong = True
                break

    return new_x, new_y


# next attacker's move (MOVE command)
def next_move(hero, monsters):
    global reached_base_att, move_up_att
    # pushed
    if distance_to_enemy_base(hero) > 6000:
        reached_base_att = False

    if not reached_base_att:
        goal_x = default_pos_left[2][0]
        goal_y = default_pos_left[2][1]

        if not started_top_left:
            goal_x = default_pos_right[2][0]
            goal_y = default_pos_right[2][1]

        dist_final = distance(hero.x, hero.y, goal_x, goal_y)
        print(f"dist_final {dist_final}, goal: {(goal_x, goal_y)}, hero: {(hero.x, hero.y)}", file=sys.stderr,
              flush=True)

        # smooth movement
        if dist_final < 800:
            reached_base_att = True

        # farm during movement
        targets = []
        for monster in monsters:
            if not will_monster_hit_enemy(monster):
                targets.append((monster, distance_e(hero, monster)))

        targets.sort(key=lambda x: x[1])

        if targets and (my_mana < 150):
            next_pos = monster_pos_next_turn(targets[0][0])

            # TODO: may be too big? -> how to separate logic here
            if distance(hero.x, hero.y, next_pos[0], next_pos[1]) <= 1000:
                print(f'MOVE {next_pos[0]} {next_pos[1]} move base-farm')
                return

        print(f'MOVE {goal_x} {goal_y} move base')
        return

    # reached base already, now scan
    # TODO: more points?
    endpoints_l = endpoints
    if not started_top_left:
        endpoints_l = endpoints_r

    # currently moving upwards (or downward symmetric)
    if move_up_att:
        dist_final = distance(hero.x, hero.y, endpoints_l[1][0], endpoints_l[1][1])
        if dist_final <= 1200:  # not 800, for more smooth movement
            move_up_att = False

        new_x, new_y = random_non_opponent(endpoints_l[1][0], endpoints_l[1][1], monsters)
        print(f'MOVE {new_x} {new_y} move down')
        return

    # currently moving downwards (or downward symmetric)
    if not move_up_att:
        dist_final = distance(hero.x, hero.y, endpoints_l[0][0], endpoints_l[0][1])
        if dist_final <= 1200:
            move_up_att = True

        new_x, new_y = random_non_opponent(endpoints_l[0][0], endpoints_l[0][1], monsters)
        print(f'MOVE {new_x} {new_y} move up')
        return


attacker_seen = 0  # how many turns ago was an attacker seen
attacker_coords = (0, 0)  # his coords
attacker_id = None
attacker_our_base = None

turn = 0
# game loop
while True:
    turn += 1
    my_health, my_mana = [int(j) for j in input().split()]
    enemy_health, enemy_mana = [int(j) for j in input().split()]
    entity_count = int(input())  # Amount of heroes and monsters you can see

    monsters = []
    my_heroes = []
    opp_heroes = []

    for i in range(entity_count):
        _id, _type, x, y, shield_life, is_controlled, health, vx, vy, near_base, threat_for = [int(j) for j in
                                                                                               input().split()]
        entity = Entity(
            _id,  # _id: Unique identifier
            _type,  # _type: 0=monster, 1=your hero, 2=opponent hero
            x, y,  # x,y: Position of this entity
            shield_life,  # shield_life: Ignore for this league; Count down until shield spell fades
            is_controlled,  # is_controlled: Ignore for this league; Equals 1 when this entity is under a control spell
            health,  # health: Remaining health of this monster
            vx, vy,  # vx,vy: Trajectory of this monster
            near_base,  # near_base: 0=monster with no target yet, 1=monster targeting a base
            threat_for
            # threat_for: Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
        )

        if _type == TYPE_MONSTER:
            monsters.append(entity)
        elif _type == TYPE_MY_HERO:
            my_heroes.append(entity)
        elif _type == TYPE_OP_HERO:
            opp_heroes.append(entity)
        else:
            assert False

    # DEFENCE
    # ------------------------------------------------------------------------------------------------------------
    # find potential targets and sort by turns to base
    targets = []
    targets_turns = []  # in how many turns will it reach out base
    for monster in monsters:
        dist, method = calc_turn_attack_min(monster, opp_heroes)
        if dist < 20:
            targets.append((monster, dist, method))
            targets_turns.append(dist)

    # sort by turns to base
    if targets:
        targets.sort(key=lambda x: x[1])

    base_in_danger = 0  # 0 - not in danger, 1 - needs one, 2 - wind, 3 - two + wind

    # check if opponent is close
    # and save his coords (if he goes missing later)
    if opp_heroes:
        for hero in opp_heroes:
            if distance_to_own_base(hero) < 6000:
                attacker_seen = 0
                attacker_coords = (hero.x, hero.y)
                attacker_id = hero.id
                attacker_our_base = hero
            else:
                attacker_seen += 1
    else:
        attacker_seen = 100

    # monsters in range for wind(1280)
    in_range_wind = 0
    # move one of defenders in front of attacker by changing default position
    # if there is attacker with monsters close
    attacker_x, attacker_y = None, None
    attacker_id = None
    if attacker_seen < 4:
        base_in_danger += 1
        distance_c = 10000
        closest_attacker = None
        for hero in opp_heroes:
            if distance_e(my_heroes[0], hero) < distance_c:
                distance_c = distance_e(my_heroes[0], hero)
                closest_attacker = hero

        if closest_attacker is None:
            new_x, new_y = attacker_coords
        else:
            new_x, new_y = closest_attacker.x, closest_attacker.y
            attacker_id = closest_attacker.id
            attacker_our_base = closest_attacker

        attacker_x, attacker_y = new_x, new_y
        for monster in monsters:
            next_pos = monster_pos_next_turn(monster)
            # TODO: more than 1280?
            if distance(new_x, new_y, next_pos[0], next_pos[1]) <= 1280 + 1280:
                in_range_wind += 1

        if not in_monster_range(new_x, new_y, monsters, 1600):
            default_pos_left = [(7300, 2300), (3500, 6800), (13600, 5000)]
            default_pos_right = [(17630 - x, 9000 - y) for (x, y) in default_pos_left]
        else:
            if new_x - 400 >= 0:
                new_x -= 400
            if new_y - 400 >= 0:
                new_y -= 400

            default_pos_left = [(new_x, new_y), (3500, 6800), (13600, 5000)]
            default_pos_right = [(17630 - x, 9000 - y) for (x, y) in default_pos_left]
    else:
        default_pos_left = [(7300, 2300), (3500, 6800), (13600, 5000)]
        default_pos_right = [(17630 - x, 9000 - y) for (x, y) in default_pos_left]

    # 2 attackers -> assign closest from the two
    if len(targets) == 1:
        if is_closer(my_heroes[0], my_heroes[1], targets[0][0]):
            is_attacking = [targets[0][0], None]
        else:
            is_attacking = [None, targets[0][0]]

    # more than one target
    if len(targets) > 1:
        if is_closer(my_heroes[0], my_heroes[1], targets[0][0]):
            is_attacking = [targets[0][0], targets[1][0]]
        else:
            is_attacking = [targets[1][0], targets[0][0]]

    monster_in_radius = 0
    for monster in targets:
        monster = monster[0]
        if distance_to_own_base(monster) < 5000:
            monster_in_radius += 1

    if monster_in_radius > 1:
        base_in_danger += 1

    if monster_in_radius > 2:
        base_in_danger += 1

    if len(targets) > 1 and targets[0][1] < 4:
        is_attacking[1] = targets[0][0]
        is_attacking[0] = targets[0][0]

    print(f"danger_level {base_in_danger}", file=sys.stderr, flush=True)

    # always attacking the closest monster from those closest to the base
    for i in range(heroes_per_player - 1):
        # To debug: print("Debug messages...", file=sys.stderr, flush=True)
        # In the first league: MOVE <x> <y> | WAIT; In later leagues: | SPELL <spellParams>;

        if distance_to_own_base(my_heroes[i]) > 12000:  # got too far by farming
            return_to_position(i, monsters)
            print(f"{i} returning from farming", file=sys.stderr, flush=True)
            continue

        # check if attacked died
        if (is_attacking[i] is not None) and is_monster_dead(is_attacking[i], monsters):
            is_attacking[i] = None

        # is currently fighting
        if is_attacking[i] is not None:
            turns_takedown = calc_turn_attack_min(is_attacking[i], opp_heroes)
            print(f"{i} has {turns_takedown}", file=sys.stderr, flush=True)
            print(f"is_attacking health: {is_attacking[i].health}", file=sys.stderr, flush=True)
            if is_attacking[i].health <= 0:
                return_to_position(i, monsters)
                continue

            # if it will destroy base
            health = is_attacking[i].health  # 2 damage per turn, 400 units
            danger = health - 2 * (turns_takedown[0] - ((distance_e(my_heroes[i], is_attacking[i]) - 800) / 400))

            print(f"{i} has danger: {danger}, in_range_wind: {in_range_wind}", file=sys.stderr, flush=True)

            opposite_x = attacker.x - attacker.vx
            opposite_y = attacker.y - attacker.vy

            # in danger and multiple in range of push
            if danger > 0 and in_range_wind >= 1 and (my_mana >= 10):
                if distance(my_heroes[i].x, my_heroes[i].y, is_attacking[i].x, is_attacking[i].y) < 1280:
                    print(f'SPELL WIND {base_opp_x} {base_opp_y} horde-push-monster')
                    my_mana -= 10
                    continue

            if danger >= -2 and in_range_wind >= 3 and (my_mana >= 10) and (attacker_x is not None):
                if distance(my_heroes[i].x, my_heroes[i].y, attacker_x, attacker_y) < 2200 and (
                        attacker_our_base.shield_life == 0):
                    print(f'SPELL CONTROL {attacker_id} {base_opp_x} {base_opp_y} horde-control-hero')
                    my_mana -= 10
                    continue

            # not using control here -> it will stil go back!
            # in danger and 1 in range of control
            # if danger > 0 and in_range_wind < 2 and (my_mana >= 10):
            #    if distance(my_heroes[i].x, my_heroes[i].y, is_attacking[i].x, is_attacking[i].y) < 2200:
            #        if distance_to_own_base(is_attacking[i]) < 1000:
            #            print(f'SPELL CONTROL {is_attacking[i].id} {base_opp_x} {base_opp_y} horde-control-monster')
            #            my_mana -= 10
            #            continue

            if base_in_danger >= 3 and (my_mana >= 10) and (distance_e(my_heroes[i], is_attacking[i]) < 1280):
                print(f'SPELL WIND {base_opp_x} {base_opp_y} horde-push-danger')
                my_mana -= 10
                continue

            # is in radius and has a lot of mana
            if (distance_to_own_base(is_attacking[i]) < 5000) and (my_mana >= 90) and (
                    distance_e(my_heroes[i], is_attacking[i]) < 1280):
                # TODO: check if it can be killed normally
                if is_attacking[i].health - ((turns_takedown[0] - 1) * 2) > 0:
                    print(f'SPELL WIND {opposite_x} {opposite_y} push')
                    my_mana -= 10
                    continue

            if (danger > 0) and (my_mana >= 10) and (distance_e(my_heroes[i], is_attacking[i]) < 1280):
                print(f'SPELL WIND {base_opp_x} {base_opp_y} danger')
                continue

            # there is an attacker near base
            # if attacker_seen < 4 and i == 0 and (distance_to_own_base(is_attacking[i])) > 5000:
            #    return_to_position(i, monsters)
            #    continue

            # attack closest
            next_pos = monster_pos_next_turn(is_attacking[i])
            print(f'MOVE {next_pos[0]} {next_pos[1]} attacking {is_attacking[i].id}')
            continue

        # is_attacking is empty meaning no monsters attacking in 20 turns

        # TODO: farm code here
        closest = None
        distance_closest = 10000
        if len(targets) > 0:
            for monster in monsters:
                if distance_e(my_heroes[i], monster) < distance_closest:
                    distance_closest = distance_e(my_heroes[i], monster)
                    closest = monster

        if closest is not None:
            next_pos = monster_pos_next_turn(closest)
            if started_top_left:
                def_coords = default_pos_left[i]
            else:
                def_coords = default_pos_right[i]

            if distance(def_coords[0], def_coords[1], next_pos[0], next_pos[1]) < 5000:
                print(f'MOVE {next_pos[0]} {next_pos[1]} farming')
                continue

        return_to_position(i, monsters)
        continue

    # ATTACK
    # ------------------------------------------------------------------------------------------------------------
    # TODO: those moving in base direction -> push & shield
    # TODO: those moving in opposite -> control
    # move or farm during movement
    attacker = my_heroes[2]
    if distance_to_enemy_base(attacker) > 6500:
        reached_base_att = False

    if not reached_base_att:
        next_move(attacker, monsters)
        continue

    # check all targets and sort by distance to them in next turn
    att_targets = []
    for monster in monsters:
        next_pos = monster_pos_next_turn(monster)
        att_targets.append(
            (monster, distance(attacker.x, attacker.y, next_pos[0], next_pos[1]), distance_to_enemy_base(monster)))

    att_targets_base = []  # moving in opponent's base direction
    att_targets_else = []  # moving elsewhere

    if att_targets:
        att_targets.sort(key=lambda x: x[1])

    for target in att_targets:
        if target[0].threat_for == 2:
            att_targets_base.append(target)
        else:
            att_targets_else.append(target)

    # find closest attacking monster
    best_dist_att = 100000
    best_attacked = None
    if att_targets_base:
        for target in att_targets_base:
            new_dist = target[1]

            # TODO:
            # check how many opponents there are
            # calculate if they will kill it
            if target[0].health < 6 and distance_to_enemy_base(target[0]) > 3000:
                continue

            if new_dist < best_dist_att:
                best_dist_att = new_dist
                best_attacked = target[0]

    # closest to base
    closest_base = []
    for target in att_targets_base:
        if target[0].health > 4 and target[2] < 3000:
            closest_base.append(target)

    if closest_base:
        closest_base.sort(key=lambda x: x[2])
        best_attacked = closest_base[0][0]

        # push if in range
        if best_dist_att < 1280:
            if my_mana >= 10:
                if best_attacked.shield_life == 0:
                    print(f'SPELL WIND {base_opp_x} {base_opp_y} push_base-follow')
                    my_mana -= 10
                    continue

        # shield attacking the base
        if best_attacked:
            if att_targets_base and my_mana >= 10 and best_attacked.shield_life == 0 and att_targets_base[0][
                0].health >= 20:
                dist = distance_e(best_attacked, attacker)
                if dist <= 2200:
                    print(f'SPELL SHIELD {best_attacked.id} shield attacker-follow')
                    my_mana -= 10
                    continue

        # push out heroes
        target_heroes = []
        for hero in opp_heroes:
            if (my_mana > 20 or enemy_health == 1) and distance_e(attacker, hero) <= 2200 and (hero.shield_life == 0):
                target_heroes.append(hero)

        if target_heroes:
            target_hero = target_heroes[0]
            dist_hero = distance_to_enemy_base(target_hero)
            for hero in target_heroes:
                if distance_to_enemy_base(hero) < dist_hero:
                    target_hero = hero
                    dist_hero = distance_to_enemy_base(hero)

            print(f'SPELL CONTROL {target_hero.id} {base_x} {base_y} control base-follow')
            my_mana -= 10
            continue

        next_pos = monster_pos_next_turn(closest_base[0][0])
        if distance(attacker.x, attacker.y, next_pos[0], next_pos[1]) <= 1200:
            print(f'WAIT attacking-wait')
            continue

        print(f'MOVE {next_pos[0]} {next_pos[1]} attacking-follow')
        continue

    # push if in range
    if best_dist_att < 1280:
        if my_mana >= 10:
            if best_attacked.shield_life == 0:
                print(f'SPELL WIND {base_opp_x} {base_opp_y} push_base')
                my_mana -= 10
                continue

    # shield attacking the base
    if best_attacked:
        if att_targets_base and my_mana >= 30 and best_attacked.shield_life == 0 and att_targets_base[0][
            0].health >= 20:
            dist = distance_e(best_attacked, attacker)
            if dist <= 2200:
                print(f'SPELL SHIELD {best_attacked.id} shield attacker')
                my_mana -= 10
                continue

    # push elsewhere
    if att_targets_else:
        if my_mana >= 30 or enemy_health == 1:
            dist = distance_e(att_targets_else[0][0], attacker)
            if dist <= 1280 and (att_targets_else[0][0].shield_life == 0):
                print(f'SPELL WIND {base_opp_x} {base_opp_y} push-else')
                my_mana -= 10
                continue

    # push out heroes
    target_heroes = []
    for hero in opp_heroes:
        if (my_mana > 40 or enemy_health == 1) and distance_e(attacker, hero) <= 2200 and (hero.shield_life == 0):
            target_heroes.append(hero)

    if target_heroes:
        target_hero = target_heroes[0]
        dist_hero = distance_to_enemy_base(target_hero)
        for hero in target_heroes:
            if distance_to_enemy_base(hero) < dist_hero:
                target_hero = hero
                dist_hero = distance_to_enemy_base(hero)

        print(f'SPELL CONTROL {target_hero.id} {base_x} {base_y} control base')
        my_mana -= 10
        continue

    if my_mana >= 10 and best_dist_att < 3000:
        next_pos = monster_pos_next_turn(att_targets[0][0])
        print(f'MOVE {next_pos[0]} {next_pos[1]} attacking')
        continue
    else:
        next_move(my_heroes[2], monsters)
        continue
