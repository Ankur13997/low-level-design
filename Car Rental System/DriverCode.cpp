#include <bits/stdc++.h>
#include <thread>
#include "CarRentalSystem.h"
#include "Bill.h"
#include "Payment.h"
using namespace std;

vector<shared_ptr<User>> createUsers(int n = 5) {
    vector<shared_ptr<User>> users;
    for (int i = 1; i <= n; ++i) {
        users.emplace_back(make_shared<User>("User" + to_string(i), "License" + to_string(i)));
    }
    return users;
}

vector<shared_ptr<Vehicle>> createVehicles(int n = 15) {
    vector<shared_ptr<Vehicle>> vehicles;
    for (int i = 1; i <= n; ++i) {
        vehicles.emplace_back(make_shared<CarVehicle>("Company" + to_string(i), 10 + 5 * i, 200 + 2 * i));
    }
    return vehicles;
}

vector<shared_ptr<Store>> createStores(int n = 10) {
    vector<shared_ptr<Store>> stores;
    for (int i = 0; i < n; ++i) {
        stores.emplace_back(make_shared<Store>());
    }
    return stores;
}

void distributeVehiclesToStores(const vector<shared_ptr<Store>>& stores, const vector<shared_ptr<Vehicle>>& vehicles) {
    for (int i = 0; i < min((int)vehicles.size(), (int)stores.size() * 2); ++i) {
        stores[i / 2]->addVehicleToInventory(vehicles[i]);
    }
}

void mapStoresToCities(CarRentalSystem& system, const vector<shared_ptr<Store>>& stores) {
    system.addstore(City::NAGPUR, stores[0]);
    system.addstore(City::NAGPUR, stores[4]);
    system.addstore(City::DELHI, stores[1]);
    system.addstore(City::MUMBAI, stores[2]);
    system.addstore(City::PUNE, stores[3]);
}

void simulateConcurrentReservations(shared_ptr<Store> store, shared_ptr<Vehicle> vehicle,
                                    const vector<shared_ptr<User>>& users, vector<shared_ptr<Reservation>>& reservations) {
    mutex reservationMutex; // Protect shared output vector

    vector<thread> threads;
    for (size_t i = 0;i < users.size(); ++i) {
        threads.emplace_back([&, i]() {
            auto r = store->createReservation(users[i], vehicle);
            if (r != nullptr) {
                lock_guard<mutex> lock(reservationMutex);
                reservations.push_back(r);
            }
        });
    }
    for (auto& t : threads) t.join();
}

void simulatethread(shared_ptr<Store>store,shared_ptr<User>user,shared_ptr<Vehicle>vehicle)
{
    auto r=store->createReservation(user,vehicle);
    if(r)
    {
        lock_guard<mutex>lock(consoleMutex);
        shared_ptr<Bill> bill = make_shared<Bill>(r);
        Payment payment(bill);
    }
}

int main() {
    CarRentalSystem system;

    auto users = createUsers();
    auto vehicles = createVehicles();
    auto stores = createStores();

    distributeVehiclesToStores(stores, vehicles);
    mapStoresToCities(system, stores);

    vector<shared_ptr<Store>> nagpurStores = system.storeController->getStoreByCity(City::NAGPUR);
    auto availableVehicles = nagpurStores[0]->getallVehicles();

    cout << "Before Status: " << availableVehicles[0]->getVehicleStatus() << endl;
    cout << "User 0 ID: " << users[0]->getId() << endl;

    thread t1(simulatethread,nagpurStores[0],users[0],availableVehicles[0]);
    thread t2(simulatethread,nagpurStores[0],users[1],availableVehicles[0]);
    thread t3(simulatethread,nagpurStores[0],users[2],availableVehicles[0]);
    thread t4(simulatethread,nagpurStores[0],users[2],availableVehicles[1]);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // vector<shared_ptr<Reservation>> successfulReservations;
    // simulateConcurrentReservations(nagpurStores[0], availableVehicles[0], users, successfulReservations);

    // // Handle billing for successful reservation(s)
    // for (auto& r : successfulReservations) {
    //     shared_ptr<Bill> bill = make_shared<Bill>(r);
    //     Payment payment(bill);
    // }

    cout << "After Status: " << availableVehicles[0]->getVehicleStatus() << endl;

    return 0;
}
