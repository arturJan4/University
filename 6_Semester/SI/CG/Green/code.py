import copy
import math
import random
import sys
from collections import namedtuple
from enum import Enum
from operator import add


class CardType(Enum):
    TRAINING = 0
    CODING = 1
    DAILY_ROUTINE = 2
    TASK_PRIORITIZATION = 3
    ARCHITECTURE_STUDY = 4
    CONTINUOUS_INTEGRATION = 5
    CODE_REVIEW = 6
    REFACTORING = 7
    BONUS = 8
    TECHNICAL_DEBT = 9


# Complete the hackathon before your opponent by following the principles of Green IT

Application = namedtuple('Application', ['id', 'card_needed'])
Cards = namedtuple('Card', ['location', 'cards_count'])


def total_cost(app):
    """total application cost in points"""
    sum = 0
    for cost in app.card_needed:
        sum += cost

    return sum


def count_shoddy(cards):
    """count all possible shoddy points from cards without bonuses"""
    sum = 0
    for i in range(0, 7):
        sum += cards.cards_count[i] * 2

    return sum


def get_debt(app, cards):
    """count how much debts releasing app generates, given you have cards, return None if not possible to release"""
    debt = 0
    bonus_count = cards.cards_count[CardType.BONUS.value]
    shoddy_count = count_shoddy(cards) + bonus_count

    # for each card type needed
    for card_type, cost in enumerate(app.card_needed):
        have = cards.cards_count[card_type]  # have specific skill -> use it

        # each card i have gives 2 points to specific skill
        needed = math.ceil(cost / 2)

        # have enough specific cards
        if have >= needed:
            continue

        cost -= have * 2  # used good points

        # use bonus cards to fill (1 good points per card)
        if bonus_count >= cost:
            bonus_count -= cost
            continue

        cost -= bonus_count

        # use shoddy points and increase debt
        if shoddy_count >= cost:
            shoddy_count -= cost
            debt += cost
            continue

        if cost == 0:
            continue
        else:
            return None

    return debt


def apps_by_cost(apps):
    """return all apps of total cost (not debt)"""
    costs = {app.id: total_cost(app) for app in apps}
    costs_sorted = sorted(costs.items(), key=lambda x: x[1])
    costs_filtered = [(k, v) for k, v in costs_sorted if v == costs_sorted[0][1]]
    return costs_filtered


def possible_apps_by_weight(apps, cards):
    """return apps possible to release with lowest debt"""
    # for app in apps:
    #    print(app, file=sys.stderr)
    debts = {app.id: get_debt(app, cards) for app in apps}
    debts = {k: v for k, v in debts.items() if v is not None}
    debts_sorted = sorted(debts.items(), key=lambda x: x[1])
    debts_filtered = [(k, v) for k, v in debts_sorted if v == debts_sorted[0][1]]
    return debts_filtered


def get_app_by_id(apps, id):
    """search for app using it's id"""
    for app in apps:
        if app.id == id:
            return app
    return None


def has_good_cards_in_hand(cards, focused_app):
    """ return true if there are good  cards in hand"""
    needed_cards = focused_app.card_needed

    for it, card in enumerate(needed_cards):
        if card <= 0:  # card is not need
            continue

        # card is needed and is in hand
        if cards.cards_count[it] > 0:
            return True

    return False


def should_wait_for_app_release(apps_released, app, cards):
    """wait for release, used for heuristics"""
    if app is None:
        return False

    debt = get_debt(app, cards)
    if debt is None:
        return False

    if debt == 0:
        return True

    if apps_released < 4:
        if debt < 2 + (apps_released * 1.5):
            # print("WAIT r<4")
            return True

    if apps_released == 4:
        if debt == 0:
            # print("WAIT r=4")
            return True

    return False


def should_wait_for_release(apps_released, debts):
    """don't play cards, wait for release"""
    if not debts:
        return False

    chosen = random.choice(debts)
    lowest_id, lowest_debt = chosen

    if lowest_debt == 0:
        print("WAIT r<4")
        return True

    if apps_released < 4:
        if lowest_debt < 2 + (apps_released * 1.5):
            print("WAIT r<4")
            return True

    if apps_released == 4:
        if lowest_debt == 0:
            print("WAIT r=4")
            return True

    return False


def should_use_prioritize(app, hand):
    take = None
    throw = None

    if hand.cards_count[CardType.TASK_PRIORITIZATION.value] == 0:
        return None, None

    minimum = 10000
    for i, cnt in enumerate(app.card_needed):
        if i == CardType.TASK_PRIORITIZATION.value and hand.cards_count[CardType.TASK_PRIORITIZATION.value] <= 1:
            continue

        if (throw is None) and (hand.cards_count[i] > 0) and (hand.cards_count[i] * 2 > cnt):
            throw = i

        if hand.cards_count[i] * 2 >= cnt:
            continue

        diff = hand.cards_count[i] * 2 - cnt
        if diff < minimum:
            take = i
            minimum = diff

    if (take is not None) and (throw is not None):
        return throw, take

    return None, None


def input_application():
    """ wrap input for application"""
    # training_needed: number of TRAINING skills needed to release this application
    # coding_needed: number of CODING skills needed to release this application
    # daily_routine_needed: number of DAILY_ROUTINE skills needed to release this application
    # task_prioritization_needed: number of TASK_PRIORITIZATION skills needed to release this application
    # architecture_study_needed: number of ARCHITECTURE_STUDY skills needed to release this application
    # continuous_delivery_needed: number of CONTINUOUS_DELIVERY skills needed to release this application
    # code_review_needed: number of CODE_REVIEW skills needed to release this application
    # refactoring_needed: number of REFACTORING skills needed to release this application
    object_type, _id, training_needed, coding_needed, daily_routine_needed, task_prioritization_needed, architecture_study_needed, continuous_delivery_needed, code_review_needed, refactoring_needed = input().split()
    _id = int(_id)
    training_needed = int(training_needed)
    coding_needed = int(coding_needed)
    daily_routine_needed = int(daily_routine_needed)
    task_prioritization_needed = int(task_prioritization_needed)
    architecture_study_needed = int(architecture_study_needed)
    continuous_delivery_needed = int(continuous_delivery_needed)
    code_review_needed = int(code_review_needed)
    refactoring_needed = int(refactoring_needed)
    application = Application(_id, [training_needed, coding_needed, daily_routine_needed, task_prioritization_needed,
                                    architecture_study_needed, continuous_delivery_needed, code_review_needed,
                                    refactoring_needed])
    # print(application, file=sys.stderr)
    # print(f"cost: {total_cost(application)}", file=sys.stderr)
    return application


def input_card():
    """wrap input for card"""
    # cards_location: the location of the card list. It can be HAND, DRAW, DISCARD or OPPONENT_CARDS (AUTOMATED and OPPONENT_AUTOMATED will appear in later leagues)
    cards_location, training_cards_count, coding_cards_count, daily_routine_cards_count, task_prioritization_cards_count, architecture_study_cards_count, continuous_delivery_cards_count, code_review_cards_count, refactoring_cards_count, bonus_cards_count, technical_debt_cards_count = input().split()
    training_cards_count = int(training_cards_count)
    coding_cards_count = int(coding_cards_count)
    daily_routine_cards_count = int(daily_routine_cards_count)
    task_prioritization_cards_count = int(task_prioritization_cards_count)
    architecture_study_cards_count = int(architecture_study_cards_count)
    continuous_delivery_cards_count = int(continuous_delivery_cards_count)
    code_review_cards_count = int(code_review_cards_count)
    refactoring_cards_count = int(refactoring_cards_count)
    bonus_cards_count = int(bonus_cards_count)
    technical_debt_cards_count = int(technical_debt_cards_count)

    card_count = Cards(cards_location, [training_cards_count, coding_cards_count, daily_routine_cards_count,
                                        task_prioritization_cards_count, architecture_study_cards_count,
                                        continuous_delivery_cards_count, code_review_cards_count,
                                        refactoring_cards_count, bonus_cards_count, technical_debt_cards_count])

    # print(card_count, file=sys.stderr)
    return card_count


def empty_card(location):
    return Cards(location, [0, 0, 0, 0, 0, 0, 0, 0, 0, 0])


focused_app = None  # id of app currently focused on
apps_released = 0  # how many apps were released
iteration = 0  # not used
current_desk = None  # where is the player

player_hand = empty_card("HAND")
player_hand_len = None
opponent_cards = empty_card("OPPONENT_CARDS")
player_draw = empty_card("DRAW")
player_discard = empty_card("DISCARD")
player_played = empty_card("PLAYED_CARDS")
opponent_automated = empty_card("OPPONENT_AUTOMATED")
player_automated = empty_card("PLAYER_AUTOMATED")

played_architecture = 0  # how many architecture cards were played till last release (draw size)
applications = []

# game loop
while True:
    game_phase = input()  # can be MOVE, GIVE_CARD, THROW_CARD, PLAY_CARD or RELEASE
    applications_count = int(input())

    if applications_count:
        applications = []
        for i in range(applications_count):
            applications.append(input_application())

    # for i in range(2):
    # player_location: id of the zone in which the player is located
    # player_permanent_daily_routine_cards: number of DAILY_ROUTINE the player has played. It allows them to take cards from the adjacent zones
    # player_permanent_architecture_study_cards: number of ARCHITECTURE_STUDY the player has played. It allows them to draw more cards

    player_location, player_score, player_permanent_daily_routine_cards, player_permanent_architecture_study_cards = [
        int(j) for j in input().split()]
    other_player_location, other_player_score, other_player_permanent_daily_routine_cards, other_player_permanent_architecture_study_cards = [
        int(j) for j in input().split()]
    card_locations_count = int(input())
    for i in range(card_locations_count):
        card = input_card()
        if card.location == "HAND":
            player_hand = card
            player_hand_len = sum(card.cards_count)
        elif card.location == "DRAW":
            player_draw = card
        elif card.location == "OPPONENT_CARDS":
            opponent_cards = card
        elif card.location == "DISCARD":
            player_discard = card
        elif card.location == "PLAYED_CARDS":
            player_played = card
        elif card.location == "AUTOMATED":
            player_automated = card
        elif card.location == "OPPONENT_AUTOMATED":
            opponent_automated = card
        else:
            raise Exception(f"unexpected type {card.location}")

    possible_moves_count = int(input())
    possible_moves = []
    for i in range(possible_moves_count):
        possible_move = input()
        possible_moves.append(possible_move)

    debts = possible_apps_by_weight(applications, player_hand)
    print(f"DEBTS: {debts}", file=sys.stderr)
    if len(debts):  # there are possible apps to release
        if focused_app is None:  # and we are not focusing one one
            chosen = random.choice(debts)  # choose one of lowest
            lowest_id, lowest_debt = chosen
            focused_app = lowest_id
            print(f"changing focus to {focused_app} because it's None", file=sys.stderr)

    # there are no possible apps -> choose one of lower cost ones
    if focused_app is None:
        chosen = random.choice(apps_by_cost(applications))
        lowest_id, lowest_debt = chosen
        focused_app = lowest_id
        print(f"changing focus to {focused_app} randomly", file=sys.stderr)

    app_data = get_app_by_id(applications, focused_app)
    if app_data is None:  # should not happen?
        if len(debts):
            chosen = random.choice(debts)
        else:
            chosen = random.choice(apps_by_cost(applications))
        lowest_id, lowest_debt = chosen
        focused_app = lowest_id
        print(f"MAIN: changing focus to {focused_app} because opponent made it first", file=sys.stderr)

    # ===================================================================
    # DEBUG section
    print(f"phase: {game_phase}", file=sys.stderr)
    print(f"my_loc: {player_location}, opp_loc: {other_player_location}", file=sys.stderr)
    print("moves: ", ", ".join(possible_moves), file=sys.stderr)
    print(f"focused app: {focused_app}", file=sys.stderr)
    print(f"player_hand: {player_hand}", file=sys.stderr)
    print(f"player_hand_len: {player_hand_len}", file=sys.stderr)
    print(f"opponent_cards: {opponent_cards}", file=sys.stderr)
    print(f"player_draw: {player_draw}", file=sys.stderr)
    print(f"player_discard: {player_discard}", file=sys.stderr)
    # print(f"player_total: {player_total}", file=sys.stderr)
    print(f"player_played : {player_played}", file=sys.stderr)
    print(f"player_automated : {player_automated}", file=sys.stderr)
    print(f"opponent_automated : {opponent_automated}", file=sys.stderr)
    print(f"app-data {app_data}", file=sys.stderr)

    # In the first league: RANDOM | MOVE <zoneId> | RELEASE <applicationId> | WAIT; In later leagues: | GIVE <cardType> | THROW <cardType> | TRAINING | CODING | DAILY_ROUTINE | TASK_PRIORITIZATION <cardTypeToThrow> <cardTypeToTake> | ARCHITECTURE_STUDY | CONTINUOUS_DELIVERY <cardTypeToAutomate> | CODE_REVIEW | REFACTORING;
    if game_phase == "MOVE":
        # Write your code here to move your player
        # You must move from your desk

        player_draw_size = sum(player_draw.cards_count)
        # hand + draw -> possible to get this turn
        player_possible_cardcnt = list(map(add, player_hand.cards_count, player_draw.cards_count))
        # hand + discard -> useful if all of draw gets used
        player_hddc_cardcnt = list(map(add, player_hand.cards_count, player_discard.cards_count))
        # all cards
        player_total_cardcnt = list(map(add, player_possible_cardcnt, player_discard.cards_count))

        # TODO: use non-useful cards to throw when passing start
        non_useful_cards = [0] * 8
        # card is needed -> higher
        # discard is replacing -> calculate with added discard
        # player is near -> calculate negatively especially if we don't have bonus
        # architecture study is cool
        bad_locs = []

        if player_location != -1:
            bad_locs.append(player_location)
        if other_player_location != -1:
            bad_locs += [other_player_location, (other_player_location - 1) % 8,
                         (other_player_location + 1) % 8]

        cards_heuristics = [0.0] * 8

        # needed cards bonus
        if app_data is not None:
            for i, cnt in enumerate(app_data.card_needed):
                if i >= 8:
                    break

                if cnt == 0:
                    continue

                # is already there
                if i == player_location:
                    continue

                # need more hards then we have
                threshold = 1
                if cnt > player_hand.cards_count[i] * threshold:
                    cards_heuristics[i] += (cnt - player_hand.cards_count[i]) * 3

                if cnt > player_possible_cardcnt[i] * threshold:
                    cards_heuristics[i] += (cnt - player_possible_cardcnt[i]) * 0.6

                if cnt > player_total_cardcnt[i] * threshold:
                    cards_heuristics[i] += (cnt - player_total_cardcnt[i]) * (1 / (player_draw_size + 5))

        # stocking bonus
        for i, cnt in enumerate(player_total_cardcnt):
            if i >= 7:
                break
            cards_heuristics[i] += (1 / (cnt + 1)) * 1.0

        # training + training + release bonus
        # TODO

        # will release if move bonus
        app = get_app_by_id(applications, focused_app)
        has_good_cards_in_hand(player_hand, app)

        hand_copy = copy.copy(player_hand)

        for i in range(8):
            hand_copy.cards_count[i] += 1
            if should_wait_for_app_release(apps_released, app, hand_copy):
                cards_heuristics[i] += 1000

            hand_copy.cards_count[i] -= 1

        # useful skill bonus

        # 1) the smaller the hand -> more important architecture study is
        cards_heuristics[CardType.ARCHITECTURE_STUDY.value] += (1 / player_hand_len) * 20

        # 2) more debt and debt in hand -> need more refactoring
        if player_hand.cards_count[CardType.TECHNICAL_DEBT.value] > 0:
            cards_heuristics[CardType.REFACTORING.value] += (player_total_cardcnt[CardType.TECHNICAL_DEBT.value] / 4)

        # 3) last turn boost
        if apps_released == 4:
            cards_heuristics[CardType.ARCHITECTURE_STUDY.value] += (1 / player_hand_len) * 40

        # 4) TODO

        # daily routine bonus (impact 2 neighbours based on number of them)
        copy_heuristics = cards_heuristics.copy()

        if player_permanent_daily_routine_cards:
            for i in range(8):
                cards_heuristics[i] += (copy_heuristics[(i - 1) % 8] + copy_heuristics[
                    (i + 1) % 8]) * player_permanent_daily_routine_cards

        # earlier bonus
        for i in range(8):
            cards_heuristics[i] += (0.1 - (0.01 * i))

        # administrative task penalty
        for i in range(0, player_location):
            cards_heuristics[i] -= 10

        # bad location penalty
        bonus_in_hand = player_hand.cards_count[CardType.BONUS.value]
        bonus_total = player_total_cardcnt[CardType.BONUS.value]

        # can't move there
        if player_location != -1:
            cards_heuristics[player_location] = -100000

        # if we have bonus then it's not that bad,
        if other_player_location != -1:
            penalty = -1000 + (bonus_in_hand * 100) + (bonus_total * 10)
            cards_heuristics[other_player_location] += penalty
            cards_heuristics[(other_player_location + 1) % 8] += penalty
            cards_heuristics[(other_player_location - 1) % 8] += penalty

        # choose from heuristics (with probability)
        cards_heuristics_dict = {card: heu for card, heu in enumerate(cards_heuristics)}
        sorted_heu = sorted(cards_heuristics_dict, key=cards_heuristics_dict.get, reverse=True)

        print(f"move_heuristics {cards_heuristics_dict}", file=sys.stderr)

        while True:
            selected = None

            max_heu = 100
            for i in sorted_heu:
                # TODO can be next-to opponent if it's killer regardless
                if (cards_heuristics_dict[i] > max_heu) and (i != player_location):
                    print(f"select based on heuristics-max {i}", file=sys.stderr)
                    selected = i
                    break
                elif random.randint(0, 3) != 0:  # reroll sometimes (not best move)
                    print(f"select based on heuristics {i}", file=sys.stderr)
                    if i != player_location:
                        selected = i
                        break

                print(f"move-reroll", file=sys.stderr)

            if selected is None:
                continue

            print(f"MOVE {selected} heu: {cards_heuristics_dict[selected]}")
            break

        iteration += 1
    elif game_phase == "GIVE_CARD":
        # Starting from league 2, you must give a card to the opponent if you move close to them.
        # Write your code here to give a card
        # RANDOM | GIVE cardTypeId
        # if possible give bonus
        if player_hand.cards_count[CardType.BONUS.value] > 0:
            print(f"GIVE {CardType.BONUS.value} bonus")
        else:
            app = get_app_by_id(applications, focused_app)
            found = False

            if app is not None:
                for i, cnt in enumerate(player_hand.cards_count):
                    if i >= 8:
                        break

                    if cnt == 0:
                        continue

                    if app.card_needed[i] == 0:
                        found = True
                        print(f"GIVE {i} useless")
                        break

            if not found:
                print("RANDOM")
    elif game_phase == "THROW_CARD":
        # must throw 2 skill cards away every time you go through the administrative task desk.
        # RANDOM | THROW cardTypeId
        app = get_app_by_id(applications, focused_app)
        found = False

        if app is not None:
            for i, cnt in enumerate(player_hand.cards_count):
                if i >= 8:
                    break

                if cnt == 0:
                    continue

                if app.card_needed[i] == 0:
                    found = True
                    print(f"THROW {i}")
                    break

        if not found:
            print("RANDOM")
    elif game_phase == "PLAY_CARD":
        # Starting from league 2, you can play some cards from your hand.
        # Write your code here to play a card
        # WAIT | RANDOM | TRAINING | CODING | DAILY_ROUTINE | TASK_PRIORITIZATION <cardTypeIdToThrow> <cardTypeIdToTake> | ARCHITECTURE_STUDY | CONTINUOUS_INTEGRATION <cardTypeIdToAutomate> | CODE_REVIEW | REFACTORING

        if should_wait_for_release(apps_released, debts):
            # print("WAIT no-act")
            continue

        app_cost = total_cost(get_app_by_id(applications, focused_app))
        app = get_app_by_id(applications, focused_app)
        throw, take = should_use_prioritize(app, player_hand)

        to_play = [0] * 8
        for card in range(8):
            if player_hand.cards_count[card] < 0:
                to_play[card] -= 100000

        # training heuristic
        # draw 2 cards and play 1 more
        if player_hand.cards_count[CardType.TRAINING.value] > 0:
            if app is None:
                to_play[CardType.TRAINING.value] -= 10000
            elif app.card_needed[CardType.TRAINING.value] > 0:
                # elif has_good_cards_in_hand(player_hand, app):
                to_play[CardType.TRAINING.value] -= 10000
            else:
                to_play[CardType.TRAINING.value] += 100


        # coding
        # draw 1 card and play 2 more
        if player_hand.cards_count[CardType.CODING.value] > 0:
            if app is None:
                to_play[CardType.CardType.CODING.value] -= 10000
            elif app.card_needed[CardType.CODING.value] > 0:
                to_play[CardType.CardType.CODING.value] -= 10000
            else:
                to_play[CardType.CardType.CODING.value] += 90


        # architecture
        # one more card in hand till release of app
        if player_hand.cards_count[CardType.ARCHITECTURE_STUDY.value] > 0:
            to_play[CardType.ARCHITECTURE_STUDY.value] += (1 / player_hand_len) * 200


        # CONTINOUS INTEGRATION
        # automate card
        ci_id = None
        if player_hand.cards_count[CardType.CONTINUOUS_INTEGRATION.value] > 0:
            for i, cnt in enumerate(app.card_needed):
                if i == CardType.CONTINUOUS_INTEGRATION.value:
                    continue

                if player_automated.cards_count[i] >= cnt:
                    continue

                if player_hand.cards_count[i] == 0:
                    continue

                if cnt > 0:
                    ci_id = i
                    break

            if ci_id is None:
                to_play[CardType.CONTINUOUS_INTEGRATION.value] -= 10000
            else:
                to_play[CardType.CONTINUOUS_INTEGRATION.value] += 40

        # REFACTORING
        # remove 2 technical debt from hand -> put to board
        if player_hand.cards_count[CardType.REFACTORING.value] and player_hand.cards_count[
            CardType.TECHNICAL_DEBT.value] >= 1:
            # REFACTORING
            to_play[CardType.REFACTORING.value] += player_hand.cards_count[
            CardType.TECHNICAL_DEBT.value]


        # CODE REVIEW
        # 2 bonus skills from board to discard pile
        if player_hand.cards_count[CardType.CODE_REVIEW.value] > 0:
            to_play[CardType.CODE_REVIEW.value] += 10

        # TODO: Daily routine

        # TASK PRIORITIZATION
        if player_hand.cards_count[CardType.TASK_PRIORITIZATION.value] > 0 and (app is not None) and (
                throw is not None):
            to_play[CardType.TASK_PRIORITIZATION.value] += 10

        # whatever

    elif game_phase == "RELEASE":
        # Write your code here to release an application
        if len(debts) == 0:
            print("WAIT no-release")
            continue

        chosen = random.choice(debts)
        lowest_id, lowest_debt = chosen
        focused_app = lowest_id
        if apps_released < 4:
            if lowest_debt >= 2 + (apps_released * 1.5):
                print("WAIT <4")
                continue

        if apps_released == 4:
            if lowest_debt != 0:
                print("WAIT =4")
                continue

        print(f"getting {lowest_debt} debt", file=sys.stderr)

        print(f"RELEASE {lowest_id}")

        focused_app = None
        apps_released += 1

        # RANDOM | WAIT | RELEASE applicationId
        # print("RANDOM")
    else:
        print("RANDOM")
