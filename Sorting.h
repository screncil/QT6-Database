#ifndef SORTING_H
#define SORTING_H


class Interactions {
public:

    void insertionSortByPrice(QSqlTableModel* database_model) const {
        int rowCount = database_model->rowCount();

        for (int i = 1; i < rowCount; ++i) {
            QVariantList rowData;
            int currentPrice = database_model->data(database_model->index(i, database_model->fieldIndex("Ціна"))).toInt();
            int j = i - 1;

            while (j >= 0 && database_model->data(database_model->index(j, database_model->fieldIndex("Ціна"))).toInt() > currentPrice) {
                rowData.clear();
                for (int column = 0; column < database_model->columnCount(); ++column) {
                    rowData << database_model->data(database_model->index(j, column));
                }

                for (int column = 0; column < database_model->columnCount(); ++column) {
                    database_model->setData(database_model->index(j + 1, column), rowData[column]);
                }
                --j;
            }

            rowData.clear();
            for (int column = 0; column < database_model->columnCount(); ++column) {
                rowData << database_model->data(database_model->index(i, column));
            }

            for (int column = 0; column < database_model->columnCount(); ++column) {
                database_model->setData(database_model->index(j + 1, column), rowData[column]);
            }
        }
    };

#endif // SORTING_H

